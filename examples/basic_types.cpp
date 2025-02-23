#include <iostream>

#include "simple-args-parser.hpp"

template <typename T>
void GetAndPrintValue(const args::Parser &parser, const std::string &name)
{
    auto val = parser.GetOptValue<T>(name);

    if (val)
    {
        std::cout << "Option (" << name << ") - value: " << *val << std::endl;
    }
    else
    {
        std::cout << "No option (" << name << ")" << std::endl;
    }
}

int main(int argc, char **argv)
{
    args::Parser args_parser(args::ParserMode::IGNORE_UNKNOWN_ARGUMENTS);

    args_parser.SetOpt<int>          ({"-i" , "--int"   , "--integer"        }, args::ArgType::ARGS_REQUIRED, "Int description"          );
    args_parser.SetOpt<long>         ({"-l" , "--long"                       }, args::ArgType::ARGS_REQUIRED, "Long description"         );
    args_parser.SetOpt<unsigned int> ({"-ui", "--uint"  , "--unsignedinteger"}, args::ArgType::ARGS_REQUIRED, "Unsigned int description" );
    args_parser.SetOpt<unsigned long>({"-ul", "--ulong" , "--unsignedlong"   }, args::ArgType::ARGS_REQUIRED, "Unsigned long description");
    args_parser.SetOpt<double>       ({"-d" , "--double"                     }, args::ArgType::ARGS_REQUIRED, "Double description"       );
    args_parser.SetOpt<float>        ({"-f" , "--float"                      }, args::ArgType::ARGS_REQUIRED, "Float description"        );
    args_parser.SetOpt<std::string>  ({"-s" , "--string"                     }, args::ArgType::ARGS_REQUIRED, "String description"       );

    args_parser.Parse(argc, argv);

    GetAndPrintValue<int>          (args_parser, "-i");
    GetAndPrintValue<long>         (args_parser, "-l");
    GetAndPrintValue<unsigned int> (args_parser, "-ui");
    GetAndPrintValue<unsigned long>(args_parser, "-ul");
    GetAndPrintValue<double>       (args_parser, "-d");
    GetAndPrintValue<float>        (args_parser, "-f");
    GetAndPrintValue<std::string>  (args_parser, "-s");

    return 0;
}