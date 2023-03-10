#include <iostream>
#include "coderatny_args.hpp"

int main(int argc, char *argv[])
{
    coderatny::arg_parser args;
    args.set_opt("-aboba", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_INT, "for amogus");
    args.set_opt("-mine", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_INT, "for vladislave");

    args.set_opt("-ya", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_INT, "for vladislave");
    args.set_opt("-lol", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_INT, "for vladislave");

    args.set_opt("-a", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_INT, "for vladislave1");
    args.set_opt("-b", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_INT, "for vladislave2");
    args.set_opt("-c", coderatny::ARGS_OPTIONAL, coderatny::ARGS_TYPE_INT, "for vladislave3");

    args.shackle_opts({"-aboba", "-mine"});
    args.shackle_opts({"-a", "-b", "-c"});

    args.parse(argc, argv);


    return 0;
}