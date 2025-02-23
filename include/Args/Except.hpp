#ifndef _EXCEPT_HPP_
#define _EXCEPT_HPP_

#include <stdexcept>

namespace args
{

struct Error : std::runtime_error
{
    explicit Error(std::string const &what) : std::runtime_error(what)
    {}
};

struct TypeError : Error
{
    explicit TypeError(std::string const &what) : Error(what)
    {}
};

struct OptionError : Error
{
    explicit OptionError(std::string const &what) : Error(what)
    {}
};

struct ParseError : Error
{
    explicit ParseError(std::string const &what) : Error(what)
    {}
};

struct CastError : ParseError
{
    explicit CastError(std::string const &what) : ParseError(what)
    {}
};

} // namespace args

#endif // _EXCEPT_HPP_
