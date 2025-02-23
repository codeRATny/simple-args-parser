#include "CastUtils.hpp"

#include <limits>

#include "Except.hpp"

namespace args::utils
{

bool Stob(const std::string &value)
{
    if (value == "on")
        return true;
    if (value == "true")
        return true;

    return false;
}

int Stoi(const std::string &str)
{
    size_t idx = 0;
    int res = 0;

    try
    {
        res = std::stoi(str, &idx);
    }
    catch (...)
    {
        throw CastError("Invalid int value");
    }

    if (idx != str.size())
        throw CastError("Invalid int value");

    return res;
}

long Stol(const std::string &str)
{
    size_t idx = 0;
    long res = 0;

    try
    {
        res = std::stol(str, &idx);
    }
    catch (...)
    {
        throw CastError("Invalid long int value");
    }

    if (idx != str.size())
        throw CastError("Invalid long int value");

    return res;
}

unsigned int Stoui(const std::string &str)
{
    size_t idx = 0;
    unsigned long res = 0;

    try
    {
        res = std::stoul(str, &idx);
    }
    catch (...)
    {
        throw CastError("Invalid unsigned int value");
    }

    if (idx != str.size())
        throw CastError("Invalid unsigned int value");

    if (res > std::numeric_limits<unsigned int>::max())
        throw CastError("Invalid unsigned int value");

    return res;
}

unsigned long Stoul(const std::string &str)
{
    size_t idx = 0;
    unsigned long res = 0;

    try
    {
        res = std::stoul(str, &idx);
    }
    catch (...)
    {
        throw CastError("Invalid unsigned long value");
    }

    if (idx != str.size())
        throw CastError("Invalid unsigned long value");

    return res;
}

float Stof(const std::string &str)
{
    size_t idx = 0;
    float res = 0.0f;

    try
    {
        res = std::stof(str, &idx);
    }
    catch (...)
    {
        throw CastError("Invalid float value");
    }

    if (idx != str.size())
        throw CastError("Invalid float value");

    return res;
}

double Stod(const std::string &str)
{
    size_t idx = 0;
    double res = 0.0f;

    try
    {
        res = std::stod(str, &idx);
    }
    catch (...)
    {
        throw CastError("Invalid double value");
    }

    if (idx != str.size())
        throw CastError("Invalid double value");

    return res;
}

} // namespace args::utils
