#include "Args/Utils.hpp"

#include "Args/Assert.hpp"

namespace args::utils
{

std::string ArgTypeToString(const ArgType type)
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

} // namespace args::utils
