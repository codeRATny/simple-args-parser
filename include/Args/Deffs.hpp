#ifndef _ARGS_DEFFS_HPP_
#define _ARGS_DEFFS_HPP_

#include <string_view>

namespace args
{

namespace type_names
{
    using sv = std::string_view;

    static constexpr auto int_type           = sv("integer");
    static constexpr auto long_type          = sv("big integer");
    static constexpr auto unsigned_int_type  = sv("unsigned integer");
    static constexpr auto unsigned_long_type = sv("unsigned big integer");
    static constexpr auto float_type         = sv("single precision float");
    static constexpr auto double_type        = sv("double precision float");
    static constexpr auto bool_type          = sv("boolean");
    static constexpr auto string_type        = sv("string");
    static constexpr auto collection_type    = sv("collection");
}

enum class ArgType
{
    ARGS_REQUIRED,
    ARGS_OPTIONAL
};

enum class ParserMode
{
    HANDLE_ALL,
    IGNORE_UNKNOWN_ARGUMENTS
};

} // namespace args

#endif // _ARGS_DEFFS_HPP_
