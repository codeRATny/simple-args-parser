#include "Args/Utils.hpp"

#include "Args/Assert.hpp"

bool args::utils::Stob(const std::string &value)
{
    if (value == "on")
        return true;
    if (value == "true")
        return true;

    return false;
}

int args::utils::Stoi(const std::string &str)
{
    size_t idx = 0;
    int res = 0;

    try
    {
        res = std::stoi(str, &idx);

    }
    catch (...)
    {
        throw std::invalid_argument("Invalid int value");
    }

    if (idx != str.size())
        throw std::invalid_argument("Invalid int value");

    return res;
}

long args::utils::Stol(const std::string &str)
{
    size_t idx = 0;
    long res = 0;

    try
    {
        res = std::stol(str, &idx);

    }
    catch (...)
    {
        throw std::invalid_argument("Invalid long int value");
    }

    if (idx != str.size())
        throw std::invalid_argument("Invalid long int value");

    return res;
}

unsigned int args::utils::Stoui(const std::string &str)
{
    size_t idx = 0;
    unsigned long res = 0;

    try
    {
        res = std::stoul(str, &idx);

    }
    catch (...)
    {
        throw std::invalid_argument("Invalid unsigned int value");
    }

    if (idx != str.size())
        throw std::invalid_argument("Invalid unsigned int value");

    if (res > std::numeric_limits<unsigned int>::max())
        throw std::invalid_argument("Invalid unsigned int value");

    return res;
}

unsigned long args::utils::Stoul(const std::string &str)
{
    size_t idx = 0;
    unsigned long res = 0;

    try
    {
        res = std::stoul(str, &idx);

    }
    catch (...)
    {
        throw std::invalid_argument("Invalid unsigned long value");
    }

    if (idx != str.size())
        throw std::invalid_argument("Invalid unsigned long value");

    return res;
}

float args::utils::Stof(const std::string &str)
{
    size_t idx = 0;
    float res = 0.0f;

    try
    {
        res = std::stof(str, &idx);

    }
    catch (...)
    {
        throw std::invalid_argument("Invalid float value");
    }

    if (idx != str.size())
        throw std::invalid_argument("Invalid float value");

    return res;
}

double args::utils::Stod(const std::string &str)
{
    size_t idx = 0;
    double res = 0.0f;

    try
    {
        res = std::stod(str, &idx);

    }
    catch (...)
    {
        throw std::invalid_argument("Invalid double value");
    }

    if (idx != str.size())
        throw std::invalid_argument("Invalid double value");

    return res;
}

std::string args::utils::OptTypeMainToString(const OptTypeMain type)
{
    switch (type)
    {
    case OptTypeMain::UNDEF:
        assert(false && "option is undef");
        break;
    case OptTypeMain::INTEGER:
        return "integer";
    case OptTypeMain::BIG_INTEGER:
        return "big integer";
    case OptTypeMain::UNSIGNED_INTEGER:
        return "unsigned integer";
    case OptTypeMain::UNSIGNED_BIG_INTEGER:
        return "unsigned big integer";
    case OptTypeMain::DOUBLE_PRECISION_FLOAT:
        return "double precision float";
    case OptTypeMain::SINGLE_PRECISION_FLOAT:
        return "single precision float";
    case OptTypeMain::BOOLEAN:
        return "boolean";
    case OptTypeMain::STRING:
        return "string";
    }

    assert(false && "unreachable");
    __builtin_unreachable();
}

std::string args::utils::OptTypeToString(const std::pair<OptTypeMain, OptTypeSub> &type)
{
    switch (type.second)
    {
    case OptTypeSub::NONE:
        return OptTypeMainToString(type.first);
    case OptTypeSub::VALUE_COLLECTION:
        return "value collection of " + OptTypeMainToString(type.first);
    }

    assert(false && "unreachable");
    __builtin_unreachable();
}

std::string args::utils::ArgTypeToString(const ArgType type)
{
    switch (type)
    {
    case ArgType::ARGS_OPTIONAL:
        return "optional";
    case ArgType::ARGS_REQUIRED:
        return "required";
    }

    assert(false && "unreachable");
    __builtin_unreachable();
}
