#include "coderatny_args.hpp"

int main(int argc, char *argv[])
{
    coderatny::arg_parser args;
    args.set_opt("-a,-A", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_VECTOR_CHAR, "for aboba");
    args.set_opt("-b", coderatny::ARGS_REQUIRED, coderatny::ARGS_TYPE_VECTOR_INT, "for amogus");
    args.set_opt("-c", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_VECTOR_FLOAT, "for cringe");
    args.set_opt("-d", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_VECTOR_STRING, "for minecraft");
    args.set_opt("-e", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_CHAR, "for me");
    args.set_opt("-f", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_INT, "for evjenya");
    args.set_opt("-g", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_FLOAT, "geting my aboba");
    args.set_opt("-h", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_STRING, "yarik");
    args.set_opt("-i", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_BOOL, "hello world");

    args.parse(argc, argv);

    auto arg_vec = args.get_args_vector<char>("-a");
    auto arg1_vec = args.get_args_vector<int>("-b");
    auto arg2_vec = args.get_args_vector<float>("-c");
    auto arg3_vec = args.get_args_vector_string("-d");

    auto arg = args.get_arg<char>("-e");
    auto arg1 = args.get_arg<int>("-f");
    auto arg2 = args.get_arg<float>("-g");
    auto arg3 = args.get_arg_string("-h");
    auto arg4 = args.get_arg<bool>("-i");

    std::cout << "parsed -a(vector char)"
              << "\n";
    for (auto &i : arg_vec)
    {
        std::cout << "\t" << i << "\n";
    }

    std::cout << "parsed -b(vector int)"
              << "\n";
    for (auto &i : arg1_vec)
    {
        std::cout << "\t" << i << "\n";
    }

    std::cout << "parsed -c(vector float)"
              << "\n";
    for (auto &i : arg2_vec)
    {
        std::cout << "\t" << i << "\n";
    }

    std::cout << "parsed -d(vector string)"
              << "\n";
    for (auto &i : arg3_vec)
    {
        std::cout << "\t" << i << "\n";
    }

    std::cout << "parsed -e(char) " << arg << "\n";
    std::cout << "parsed -f(int) " << arg1 << "\n";
    std::cout << "parsed -g(float) " << arg2 << "\n";
    std::cout << "parsed -h(string) " << arg3 << "\n";
    std::cout << "parsed -i(bool) " << arg4 << "\n";

    return 0;
}