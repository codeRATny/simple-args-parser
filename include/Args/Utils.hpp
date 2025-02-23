#ifndef _ARGS_UTILS_HPP_
#define _ARGS_UTILS_HPP_

#include <string>
#include <limits>
#include <stdexcept>

#include "Args/Deffs.hpp"
#include "Args/TypeConcepts.hpp"

namespace args::utils
{

template <typename T>
constexpr std::string_view GetTypeName()
{
    if constexpr (std::is_same_v<int, T>)
    {
        return type_names::int_type;
    }
    else if constexpr (std::is_same_v<long, T>)
    {
        return type_names::long_type;
    }
    else if constexpr (std::is_same_v<unsigned int, T>)
    {
        return type_names::unsigned_int_type;
    }
    else if constexpr (std::is_same_v<unsigned long, T>)
    {
        return type_names::unsigned_long_type;
    }
    else if constexpr (std::is_same_v<double, T>)
    {
        return type_names::double_type;
    }
    else if constexpr (std::is_same_v<float, T>)
    {
        return type_names::float_type;
    }
    else if constexpr (std::is_same_v<bool, T>)
    {
        return type_names::bool_type;
    }
    else if constexpr (details::string_constructible<T>)
    {
        return type_names::string_type;
    }
    else
    {
        []<bool flag = false>(){static_assert(flag, "Unknown type for arg parser");}();
    }

    __builtin_unreachable();
}

std::string ArgTypeToString(const ArgType type);

} // namespace args::utils

#endif // _ARGS_UTILS_HPP_
