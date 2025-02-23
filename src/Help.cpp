#include "Args/Help.hpp"

#include <iomanip>
#include <iostream>

#include "Args/Utils.hpp"

namespace args::defaults::placeholders
{

void Help(const std::unordered_map<const OptBase *, std::vector<std::string>> &options)
{
    size_t longest_name = 0;
    size_t max_aliases = 0;
    for (const auto &[opt_ptr, names] : options)
    {
        for (const auto &name : names)
        {
            longest_name = longest_name < name.size() ? name.size() : longest_name;
        }

        max_aliases = max_aliases < names.size() ? names.size() : max_aliases;
    }

    longest_name += 2;

    std::cout << "Help menu:\n";
    for (const auto &[opt_ptr, names] : options)
    {
        size_t names_count = names.size();

        for (size_t i = 0; i != names_count; i++)
        {
            if (i == 0 && names_count == 1)
            {
                std::cout << names.at(i) << "";
            }
            else if (i + 1 != names_count)
            {
                std::cout << names.at(i) << "," << std::setw(longest_name - names.at(i).size()) << "";
            }
            else if (i == names_count - 1)
            {
                std::cout << names.at(i) << std::setw(longest_name - names.at(i).size()) << "";
            }
            else
            {
                std::cout << names.at(i) << std::setw(longest_name - names.at(i).size()) << "";
            }
        }
        if (max_aliases - names_count > 0)
        {
            if (names_count == 1)
            {
                std::cout << std::setw(max_aliases * longest_name - names.back().size() + 2) << "";
            }
            else
            {
                std::cout << std::setw((max_aliases - names_count) * longest_name + 1) << "";
            }
        }

        if (opt_ptr->IsCollection())
        {
            std::cout << " | type: collection of " << opt_ptr->GetTypeName() << ", ";
        }
        else
        {
            std::cout << " | type: " << opt_ptr->GetTypeName() << ", ";
        }

        std::cout << "description: " << opt_ptr->GetDescription() << ", ";
        std::cout << utils::ArgTypeToString(opt_ptr->GetArgType()) << std::endl;
    }
}

void AfterHelp()
{
    exit(0);
}

} // namespace args::defaults::placeholders
