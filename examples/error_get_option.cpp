#include <iostream>

#include "simple-args-parser.hpp"

int main(int argc, char **argv)
{
    args::Parser args_parser(args::ParserMode::IGNORE_UNKNOWN_ARGUMENTS);

    args_parser.SetOpt<int>({"-i", "--int", "--integer"}, args::ArgType::ARGS_REQUIRED, "Int description");

    args_parser.Parse(argc, argv);

    try
    {
        auto val = args_parser.GetOptValue<double>("-i");
        std::cout << *val << std::endl;
    }
    catch(const args::TypeError &e)
    {
        std::cout << "Handle type error: " << e.what() << std::endl;
    }

    return 0;
}