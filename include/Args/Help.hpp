#ifndef _ARGS_HELP_HPP_
#define _ARGS_HELP_HPP_

#include "Args/Parser.hpp"

namespace args::defaults::placeholders
{

void Help(const std::unordered_map<const OptBase *, std::vector<std::string>> &options);

void AfterHelp();

} // namespace args::defaults::placeholders

#endif // _ARGS_HELP_HPP_
