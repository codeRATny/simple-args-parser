#ifndef _ARGS_PARSER_HPP_
#define _ARGS_PARSER_HPP_

#include <string>
#include <memory>
#include <vector>
#include <optional>
#include <functional>
#include <unordered_map>

#include "Args/Utils.hpp"
#include "Args/TypeTraits.hpp"

namespace args
{
    struct OptBase
    {
    public:
        using Ptr = std::shared_ptr<OptBase>;

        virtual void SetValue(const std::string &value) = 0;
        virtual bool HaveValue() = 0;
        virtual ArgType GetArgType() const = 0;
        virtual std::string GetDescription() const = 0;

        std::pair<OptTypeMain, OptTypeSub> GetType() const
        {
            return _opt_type;
        }

    protected:
        friend class Parser;

        std::vector<std::string> _shackled_with;
        std::pair<OptTypeMain, OptTypeSub> _opt_type = {OptTypeMain::UNDEF, OptTypeSub::NONE};
    };

    template <typename T>
    class OptTuple final : public OptBase
    {
    public:
        OptTuple()
        {
            OptBase::_opt_type = utils::GetOptType<T>();
        }

        OptTuple(const OptTuple &opt)
        {
            type = opt.type;
            description = opt.description;
            OptBase::_opt_type = opt._opt_type;
        }

        OptTuple(OptTuple &&opt)
        {
            type = opt.type;
            description = std::move(opt.description);
            OptBase::_opt_type = std::move(opt._opt_type);
        }

        bool HaveValue() override
        {
            return _value.has_value();
        }

        ArgType GetArgType() const override
        {
            return type;
        }

        std::string GetDescription() const override
        {
            return description;
        }

        void SetValue(const std::string &value) override
        {
            if constexpr (details::is_allowed_type_v<T>)
            {
                if (_value.has_value())
                    throw std::runtime_error("Argument already have value");

                auto tmp_value = utils::CastValue<T>(value);
                _value = std::move(tmp_value);
            }
            else if constexpr (details::is_insertable_v<T>)
            {
                if (!_value.has_value())
                    _value = T();

                auto tmp_value = utils::CastValue<decltype(typename T::value_type())>(value);
                _value.value().insert(std::move(tmp_value));
            }
            else if constexpr (details::is_push_backable_v<T>)
            {
                if (!_value.has_value())
                    _value = T();


                auto tmp_value = utils::CastValue<decltype(typename T::value_type())>(value);
                _value.value().push_back(std::move(tmp_value));
            }
            else if constexpr (details::is_pushable_v<T>)
            {
                if (!_value.has_value())
                    _value = T();

                auto tmp_value = utils::CastValue<decltype(typename T::value_type())>(value);
                _value.value().push(std::move(tmp_value));
            }
            else
            {
                []<bool flag = false>(){static_assert(flag, "Unknown type for arg parser");}();
            }
        }

        ArgType type;
        std::string description;

    private:
        friend class Parser;

        std::optional<T> _value;
    };

    class Parser
    {
    public:
        Parser() : _want_to_feed_value(false), _mode(ParserMode::HANDLE_ALL)
        {};

        Parser(ParserMode mode) : _want_to_feed_value(false), _mode(mode)
        {};

        void Parse(int argc, char **argv);

        void VerifyRequiredOpts();

        void VerifyShackledOpts();

        template <typename T>
        std::optional<T> GetOptValue(const std::string &opt_name)
        {
            auto opt_it = _opts.find(opt_name);
            if (opt_it == _opts.end())
                throw std::invalid_argument("Unknown option");

            auto opt_ptr = dynamic_cast<OptTuple<T>*>(opt_it->second.get());
            if (opt_ptr == nullptr)
                throw std::runtime_error("Invalid type for option");

            return opt_ptr->_value;
        }

        template <typename T>
        auto &SetOpt(const std::vector<std::string> &names, ArgType type, const std::string &description)
        {
            OptTuple<T> opt;
            opt.type = type;
            opt.description = description;
            auto opt_ptr = std::make_shared<OptTuple<T>>(std::move(opt));

            for (const auto &name : names)
            {
                _opts[name] = opt_ptr;
            }

            return *this;
        }

        void ShackleOpts(const std::vector<std::string> &shackable_opt);

        void SetHelpCb(const std::function<void(const std::unordered_map<const OptBase *, std::vector<std::string>> &)> &cb)
        {
            _help_cb = cb;
        }

        void SetAfterHelpCb(const std::function<void()> &cb)
        {
            _after_help_cb = cb;
        }

    private:

        void _FeedArg(const std::string &arg);

        void _HandleNewArg(const std::string &arg);

        void _HandleArgValue(const std::string &val);

        void _HandleHelp();

        void _HandleAfterHelp();

        std::unordered_map<std::string, OptBase::Ptr> _opts;

        OptBase::Ptr *cur_opt;

        std::function<void(const std::unordered_map<const OptBase *, std::vector<std::string>> &)> _help_cb;

        std::function<void()> _after_help_cb;

        bool _want_to_feed_value;

        ParserMode _mode;
    };
}

#endif
