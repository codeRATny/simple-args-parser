#ifndef _ARGS_UTILS_HPP_
#define _ARGS_UTILS_HPP_

#include <string>
#include <limits>
#include <stdexcept>

#include "Args/Deffs.hpp"
#include "Args/TypeTraits.hpp"

namespace args
{
    namespace utils
    {
        std::string TypeToStr(ArgType type);
        bool Stob(const std::string &str);
        int Stoi(const std::string &str);
        long Stol(const std::string &str);
        unsigned int Stoui(const std::string &str);
        unsigned long Stoul(const std::string &str);
        float Stof(const std::string &str);
        double Stod(const std::string &str);

        template <typename T>
        T CastValue(const std::string &value)
        {
            if constexpr (std::is_same_v<int, T>)
            {
                return Stoi(value);
            }
            else if constexpr (std::is_same_v<long, T>)
            {
                return Stol(value);
            }
            else if constexpr (std::is_same_v<unsigned int, T>)
            {
                return Stoui(value);
            }
            else if constexpr (std::is_same_v<unsigned long, T>)
            {
                return Stoul(value);
            }
            else if constexpr (std::is_same_v<double, T>)
            {
                return Stod(value);
            }
            else if constexpr (std::is_same_v<float, T>)
            {
                return Stof(value);
            }
            else if constexpr (std::is_same_v<bool, T>)
            {
                return Stob(value);
            }
            else if constexpr (std::is_same_v<std::string, T>)
            {
                return value;
            }
            else
            {
                []<bool flag = false>(){static_assert(flag, "Unknown type for arg parser");}();
            }

            __builtin_unreachable();
        }

        template <typename T>
        OptTypeMain GetOptMainType()
        {
            if constexpr (std::is_same_v<int, T>)
            {
                return OptTypeMain::INTEGER;
            }
            else if constexpr (std::is_same_v<long, T>)
            {
                return OptTypeMain::BIG_INTEGER;
            }
            else if constexpr (std::is_same_v<unsigned int, T>)
            {
                return OptTypeMain::UNSIGNED_INTEGER;
            }
            else if constexpr (std::is_same_v<unsigned long, T>)
            {
                return OptTypeMain::UNSIGNED_BIG_INTEGER;
            }
            else if constexpr (std::is_same_v<double, T>)
            {
                return OptTypeMain::DOUBLE_PRECISION_FLOAT;
            }
            else if constexpr (std::is_same_v<float, T>)
            {
                return OptTypeMain::SINGLE_PRECISION_FLOAT;
            }
            else if constexpr (std::is_same_v<bool, T>)
            {
                return OptTypeMain::BOOLEAN;
            }
            else if constexpr (std::is_same_v<std::string, T>)
            {
                return OptTypeMain::STRING;
            }
            else
            {
                []<bool flag = false>(){static_assert(flag, "Unknown type for arg parser");}();
            }

            __builtin_unreachable();
        }

        template <typename T>
        std::pair<OptTypeMain, OptTypeSub> GetOptType()
        {
            if constexpr (details::is_insertable_v<T> || details::is_push_backable_v<T> ||
                          details::is_pushable_v<T>)
            {
                return std::make_pair(GetOptMainType<decltype(typename T::value_type())>(), OptTypeSub::VALUE_COLLECTION);
            }
            else if constexpr (details::is_allowed_type_v<T>)
            {
                return std::make_pair(GetOptMainType<T>(), OptTypeSub::NONE);
            }
            else
            {
                []<bool flag = false>(){static_assert(flag, "Unknown type for arg parser");}();
            }

            __builtin_unreachable();
        }

        std::string OptTypeMainToString(const OptTypeMain type);
        std::string OptTypeToString(const std::pair<OptTypeMain, OptTypeSub> &type);
        std::string ArgTypeToString(const ArgType type);
    }
}

#endif
