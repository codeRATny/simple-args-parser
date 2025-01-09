#ifndef _ARGS_HELP_HPP_
#define _ARGS_HELP_HPP_

#include "Args/Parser.hpp"

namespace args
{
    namespace defaults
    {
        namespace placeholders
        {
            void Help(const std::unordered_map<const OptBase *, std::vector<std::string>> &options);

            void AfterHelp();
        }
    }
}

#endif
