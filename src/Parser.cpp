#include "Args/Parser.hpp"

#include <cstring>

#include "Args/Help.hpp"
#include "Args/Assert.hpp"

void args::Parser::Parse(int argc, char **argv)
{
    if (argc >= 2)
    {
        if (!strcmp(argv[1], "-help") || !strcmp(argv[1], "--help") ||
            !strcmp(argv[1], "-h")    || !strcmp(argv[1], "--h")    )
        {
            _HandleHelp();
            exit(0);
        }
    }

    for (int i = 1; i < argc; i++)
    {
        _FeedArg(std::string(argv[i]));
    }

    VerifyRequiredOpts();
    VerifyShackledOpts();
}

void args::Parser::VerifyRequiredOpts()
{
    for (const auto &[opt_name, opt] : _opts)
    {
        if (opt->GetArgType() == ArgType::ARGS_REQUIRED && !opt->HaveValue())
            throw std::runtime_error("Required opt " + opt_name + " don't have value");
    }
}

void args::Parser::VerifyShackledOpts()
{
    for (const auto &[opt_name, opt] : _opts)
    {
        for (const auto &shackled_opt_name : opt->_shackled_with)
        {
            auto shackled_it = _opts.find(shackled_opt_name);
            if (shackled_it == _opts.end())
                throw std::invalid_argument("Unkonwn shackled opt");

            if (!shackled_it->second->HaveValue())
                throw std::runtime_error("Shackled opt dont have value");
        }

    }
}

void args::Parser::ShackleOpts(const std::vector<std::string> &shackable_opt)
{
    for (const auto &opt_name : shackable_opt)
    {
        auto opt_it = _opts.find(opt_name);
        if (opt_it == _opts.end())
            throw std::invalid_argument("Unknown arg to shackle " + opt_name);

        auto tmp = shackable_opt;
        std::erase_if(tmp, [&](const auto &val)
        {
            return val == opt_name;
        });

        opt_it->second->_shackled_with = tmp;
    }
}

void args::Parser::_FeedArg(const std::string &arg)
{
    if (arg.starts_with("-"))
    {
        _HandleNewArg(arg);
    }
    else
    {
        _HandleArgValue(arg);
    }
}

void args::Parser::_HandleNewArg(const std::string &arg)
{
    auto opt_it = _opts.find(arg);
    if (opt_it == _opts.end())
    {
        _want_to_feed_value = false;

        if (_mode == ParserMode::HANDLE_ALL)
            throw std::invalid_argument("Unknown argument \"" + arg + "\"");

        return;
    }

    _want_to_feed_value = true;
    cur_opt = &opt_it->second;
}

void args::Parser::_HandleArgValue(const std::string &val)
{
    if (_want_to_feed_value)
    {
        assert(cur_opt != nullptr);
        (*cur_opt)->SetValue(val);
    }
}

void args::Parser::_HandleHelp()
{
    std::unordered_map<const OptBase *, std::vector<std::string>> option_aliases;

    for (const auto &[name, opt_obj] : _opts)
    {
        option_aliases[opt_obj.get()].push_back(name);
    }

    if (_help_cb)
        _help_cb(option_aliases);
    else
        defaults::placeholders::Help(option_aliases);
}

void args::Parser::_HandleAfterHelp()
{
    if (_after_help_cb)
        _after_help_cb();
    else
        defaults::placeholders::AfterHelp();
}
