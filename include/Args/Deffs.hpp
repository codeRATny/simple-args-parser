#ifndef _ARGS_DEFFS_HPP_
#define _ARGS_DEFFS_HPP_

namespace args
{
    enum class ArgType
    {
        ARGS_REQUIRED,
        ARGS_OPTIONAL
    };

    enum class OptTypeMain
    {
        UNDEF,
        INTEGER,
        BIG_INTEGER,
        UNSIGNED_INTEGER,
        UNSIGNED_BIG_INTEGER,
        DOUBLE_PRECISION_FLOAT,
        SINGLE_PRECISION_FLOAT,
        BOOLEAN,
        STRING
    };

    enum class OptTypeSub
    {
        NONE,
        VALUE_COLLECTION
    };

    enum class ParserMode
    {
        HANDLE_ALL,
        IGNORE_UNKNOWN_ARGUMENTS
    };
}

#endif
