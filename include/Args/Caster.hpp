#ifndef _CASTER_HPP_
#define _CASTER_HPP_

#include <string>

#include "CastUtils.hpp"

namespace args
{

template <typename T>
struct caster
{};

template <>
struct caster<std::string>
{
    static auto cast_value(const std::string &value)
    {
        return value;
    }
};

template <>
struct caster<int>
{
    static auto cast_value(const std::string &value)
    {
        return utils::Stoi(value);;
    }
};

template <>
struct caster<long>
{
    static auto cast_value(const std::string &value)
    {
        return utils::Stol(value);
    }
};

template <>
struct caster<unsigned int>
{
    static auto cast_value(const std::string &value)
    {
        return utils::Stoui(value);
    }
};

template <>
struct caster<unsigned long>
{
    static auto cast_value(const std::string &value)
    {
        return utils::Stoul(value);
    }
};

template <>
struct caster<double>
{
    static auto cast_value(const std::string &value)
    {
        return utils::Stod(value);
    }
};

template <>
struct caster<float>
{
    static auto cast_value(const std::string &value)
    {
        return utils::Stof(value);
    }
};

template <>
struct caster<bool>
{
    static auto cast_value(const std::string &value)
    {
        return utils::Stob(value);
    }
};

} // namespace args

#endif // _CASTER_HPP_
