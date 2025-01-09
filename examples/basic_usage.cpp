#include <set>
#include <vector>
#include <queue>
#include <iostream>

#include "simple-args-parser.hpp"

int main(int argc, char **argv)
{
    args::Parser args(args::ParserMode::IGNORE_UNKNOWN_ARGUMENTS);
    args.SetOpt<int>({"-i", "--int", "--integer"}, args::ArgType::ARGS_REQUIRED, "int number")
        .SetOpt<double>({"-d", "--double"}, args::ArgType::ARGS_OPTIONAL, "double number");

    args.SetOpt<std::vector<std::string>>({"-v"}, args::ArgType::ARGS_OPTIONAL, "vector of strings");
    args.SetOpt<std::queue<double>>({"-q"}, args::ArgType::ARGS_OPTIONAL, "queue of doubles");
    args.SetOpt<std::set<int>>({"-s"}, args::ArgType::ARGS_OPTIONAL, "set of ints");

    args.Parse(argc, argv);

    auto val1 = args.GetOptValue<std::vector<std::string>>("-v");
    auto val2 = args.GetOptValue<std::queue<double>>("-q");
    auto val3 = args.GetOptValue<std::set<int>>("-s");
    auto val4 = args.GetOptValue<int>("-i");
    auto val5 = args.GetOptValue<double>("--double");

    if (val1)
    {
        std::cout << "parsed -v (vector of string) ";
        for (auto &v : *val1)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "No opt -v" << std::endl;
    }

    if (val2)
    {
        std::cout << "parsed -q (queue of double) ";
        while (!val2->empty())
        {
            auto el = val2->front();
            std::cout << el << " ";
            val2->pop();
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "No opt -q" << std::endl;
    }

    if (val3)
    {
        std::cout << "parsed -s (set of int) ";
        for (auto &v : *val3)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "No opt -s" << std::endl;
    }

    std::cout << "parsed -i (int) " << *val4 << "\n";

    if (val5)
    {
        std::cout << "parsed -d (double) " << *val5 << "\n";
    }
    else
    {
        std::cout << "No opt -d" << std::endl;
    }

    return 0;
}