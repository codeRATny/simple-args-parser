#include <iostream>

#include <set>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <vector>
#include <forward_list>
#include <unordered_set>

#include "simple-args-parser.hpp"

/* -- Helpers functions -- */
template <typename T>
void GetAndPrintIterableContainer(const args::Parser &parser, const std::string &name);

template <typename T>
void GetAndPrintStack(const args::Parser &parser, const std::string &name);

template <typename T>
void GetAndPrintDeque(const args::Parser &parser, const std::string &name);

template <typename T>
void GetAndPrintQueue(const args::Parser &parser, const std::string &name);



int main(int argc, char **argv)
{
    args::Parser args_parser(args::ParserMode::IGNORE_UNKNOWN_ARGUMENTS);

    args_parser.SetOpt<std::stack<float>>              ({"--stack"}      , args::ArgType::ARGS_OPTIONAL, "Stack of float description"         );
    args_parser.SetOpt<std::deque<long>>               ({"--deque"}      , args::ArgType::ARGS_OPTIONAL, "Deque of long description"          );
    args_parser.SetOpt<std::queue<unsigned int>>       ({"--queue"}      , args::ArgType::ARGS_OPTIONAL, "Queue of unsigned int description"  );
    args_parser.SetOpt<std::set<double>>               ({"--set"}        , args::ArgType::ARGS_OPTIONAL, "Set of double description"          );
    args_parser.SetOpt<std::forward_list<std::string>> ({"--forwardlist"}, args::ArgType::ARGS_OPTIONAL, "Forward list of sting description"  );
    args_parser.SetOpt<std::list<int>>                 ({"--list"}       , args::ArgType::ARGS_OPTIONAL, "List of int description"            );
    args_parser.SetOpt<std::vector<int>>               ({"--vector"}     , args::ArgType::ARGS_OPTIONAL, "Vector of int description"          );
    args_parser.SetOpt<std::unordered_set<std::string>>({"--hashset"}    , args::ArgType::ARGS_OPTIONAL, "Unordered set of string description");

    args_parser.Parse(argc, argv);

    GetAndPrintStack<std::stack<float>>                          (args_parser, "--stack"      );
    GetAndPrintDeque<std::deque<long>>                           (args_parser, "--deque"      );
    GetAndPrintQueue<std::queue<unsigned int>>                   (args_parser, "--queue"      );
    GetAndPrintIterableContainer<std::set<double>>               (args_parser, "--set"        );
    GetAndPrintIterableContainer<std::forward_list<std::string>> (args_parser, "--forwardlist");
    GetAndPrintIterableContainer<std::list<int>>                 (args_parser, "--list"       );
    GetAndPrintIterableContainer<std::vector<int>>               (args_parser, "--vector"     );
    GetAndPrintIterableContainer<std::unordered_set<std::string>>(args_parser, "--hashset"    );

    return 0;
}


template <typename T>
void GetAndPrintQueue(const args::Parser &parser, const std::string &name)
{
    auto val = parser.GetOptValue<T>(name);

    if (val)
    {
        std::cout << "Option (" << name << ") - value:";

        while (val->size())
        {
            std::cout << " " << val->front() << " ";
            val->pop();
        }

        std::cout << std::endl;
    }
    else
    {
        std::cout << "No option (" << name << ")" << std::endl;
    }
}

template <typename T>
void GetAndPrintDeque(const args::Parser &parser, const std::string &name)
{
    auto val = parser.GetOptValue<T>(name);

    if (val)
    {
        std::cout << "Option (" << name << ") - value:";

        while (val->size())
        {
            std::cout << " " << val->front() << " ";
            val->pop_front();
        }

        std::cout << std::endl;
    }
    else
    {
        std::cout << "No option (" << name << ")" << std::endl;
    }
}

template <typename T>
void GetAndPrintStack(const args::Parser &parser, const std::string &name)
{
    auto val = parser.GetOptValue<T>(name);

    if (val)
    {
        std::cout << "Option (" << name << ") - value:";

        while (val->size())
        {
            std::cout << " " << val->top() << " ";
            val->pop();
        }

        std::cout << std::endl;
    }
    else
    {
        std::cout << "No option (" << name << ")" << std::endl;
    }
}

template <typename T>
void GetAndPrintIterableContainer(const args::Parser &parser, const std::string &name)
{
    auto val = parser.GetOptValue<T>(name);

    if (val)
    {
        std::cout << "Option (" << name << ") - value:";

        for (auto &element : *val)
        {
            std::cout << " " << element << " ";
        }

        std::cout << std::endl;
    }
    else
    {
        std::cout << "No option (" << name << ")" << std::endl;
    }
}
