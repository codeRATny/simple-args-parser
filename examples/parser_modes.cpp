#include <iostream>

#include "simple-args-parser.hpp"

/*
    Try for ./parser_modes -s test -unknown test
*/

int main(int argc, char **argv)
{
    args::Parser args_parser_skip_unknown(args::ParserMode::IGNORE_UNKNOWN_ARGUMENTS);
    args::Parser args_parser_handle_all  (args::ParserMode::HANDLE_ALL);

    // add identical options
    args_parser_skip_unknown.SetOpt<std::string>({"-s" , "--string"}, args::ArgType::ARGS_OPTIONAL, "String description");
    args_parser_handle_all.SetOpt<std::string>  ({"-s" , "--string"}, args::ArgType::ARGS_OPTIONAL, "String description");

    try
    {
        args_parser_skip_unknown.Parse(argc, argv);
    }
    catch(const args::ParseError &e)
    {
        // not expected exception for unknown argument
        std::cout << "Parse error (mode == args::ParserMode::IGNORE_UNKNOWN_ARGUMENTS): " << e.what() << std::endl;
    }
    catch(const std::exception &e)
    {
        // handle etc.
        std::cout << "Error: " << e.what() << std::endl;
    }

    try
    {
        args_parser_handle_all.Parse(argc, argv);
    }
    catch(const args::ParseError &e)
    {
        // expected exception for unknown argument
        std::cout << "Parse error (mode == args::ParserMode::HANDLE_ALL): " << e.what() << std::endl;
    }
    catch(const std::exception &e)
    {
        // handle etc.
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}