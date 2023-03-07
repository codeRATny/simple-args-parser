#ifndef _CODERATNY_ARGS_HPP_
#define _CODERATNY_ARGS_HPP_

#include <iostream>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

namespace coderatny
{
    enum cdrtnrgs_type
    {
        ARGS_TYPE_INT,
        ARGS_TYPE_FLOAT,
        ARGS_TYPE_CHAR,
        ARGS_TYPE_STRING,
        ARGS_TYPE_BOOL,
        ARGS_TYPE_VECTOR_INT = 10,
        ARGS_TYPE_VECTOR_FLOAT,
        ARGS_TYPE_VECTOR_CHAR,
        ARGS_TYPE_VECTOR_STRING,
    };

    enum cdrtnrgs_necessity
    {
        ARGS_REQUIRED,
        ARGS_OPTIONAL
    };

    struct opt_struct
    {
        std::vector<std::string> opts;
        cdrtnrgs_necessity necessity;
        cdrtnrgs_type type;
    };

    class arg_parser
    {
    private:
        std::unordered_map<int, std::vector<std::string>> args;
        std::vector<opt_struct> opts;

        int find_in_vector_of_vector(std::string arg)
        {
            for (size_t i = 0; i < opts.size(); i++)
            {
                if (std::find(opts[i].opts.begin(), opts[i].opts.end(), arg) != opts[i].opts.end())
                {
                    return i;
                }
            }
            return -1;
        }

        int check_type(std::vector<std::string> ar, cdrtnrgs_type type)
        {
            try
            {
                switch (type)
                {
                case ARGS_TYPE_INT:
                    std::stoi(ar[0].c_str());
                    break;

                case ARGS_TYPE_FLOAT:
                    std::stof(ar[0].c_str());
                    break;

                case ARGS_TYPE_CHAR:
                    if (ar[0].length() >= 2)
                    {
                        return -1;
                    }
                    break;

                case ARGS_TYPE_STRING:
                    break;

                case ARGS_TYPE_BOOL:
                    if ((ar[0] == "true") | (ar[0] == "false") | (ar[0] == "yes") | (ar[0] == "no") | (ar[0] == "0") | (ar[0] == "1"))
                    {
                        return 0;
                    }
                    return -1;

                case ARGS_TYPE_VECTOR_INT:

                    for (auto &i : ar)
                    {
                        std::stoi(i.c_str());
                    }
                    break;

                case ARGS_TYPE_VECTOR_FLOAT:
                    for (auto &i : ar)
                    {
                        std::stof(i.c_str());
                    }
                    break;

                case ARGS_TYPE_VECTOR_CHAR:
                    for (auto &i : ar)
                    {
                        if (i.length() >= 2)
                        {
                            return -1;
                        }
                    }
                    break;

                case ARGS_TYPE_VECTOR_STRING:
                    break;

                default:
                    return -1;
                }
            }
            catch (...)
            {
                return -1;
            }

            return 0;
        }

    public:
        void parse(int argc, char *argv[])
        {
            int idx = -1;

            for (int i = 0; i < argc; i++)
            {
                if (argv[i][0] == '-')
                {
                    idx = find_in_vector_of_vector(argv[i]);
                    if (idx == -1)
                    {
                        std::cout << "unrecognized args!\n";
                        exit(1);
                    }

                    continue;
                }

                if (idx != -1)
                {
                    args[idx].push_back(argv[i]);
                }
            }

            for (size_t i = 0; i < opts.size(); i++)
            {
                if (args.find(i) == args.end())
                {
                    if (opts[i].necessity == ARGS_OPTIONAL)
                    {
                        continue;
                    }
                    std::cout << "dont find required option! "
                              << opts[i].opts[0] << "\n";
                    exit(1);
                }

                if ((opts[i].type < 10) & (args.at(i).size() > 1))
                {
                    std::cout << "invalid args type vector "
                              << opts[i].opts[0] << "\n";
                    exit(1);
                }
                else
                {
                    if (check_type(args.at(i), opts[i].type) == -1)
                    {
                        std::cout << "invalid args type "
                                  << opts[i].opts[0] << "\n";
                        exit(1);
                    }
                }
            }
        }

        void set_opt(std::string opt, cdrtnrgs_necessity necessity, cdrtnrgs_type type)
        {
            size_t idx = opts.size();
            opts.emplace_back();
            opts[idx].necessity = necessity;
            opts[idx].type = type;

            size_t pos = 0;
            std::string token;
            while ((pos = opt.find(',')) != std::string::npos)
            {
                token = opt.substr(0, pos);
                opts[idx].opts.push_back(token);
                opt.erase(0, pos + 1);
            }
            opts[idx].opts.push_back(opt);
        }

        template <typename T>
        std::vector<T> get_args_vector(std::string arg)
        {
            std::vector<T> ret;
            int idx = find_in_vector_of_vector(arg);
            if (idx == -1)
            {
                return ret;
            }

            if (typeid(T).hash_code() == typeid(int).hash_code())
            {
                for (auto &i : args.at(idx))
                {
                    ret.push_back(std::stoi(i));
                }
            }
            else if (typeid(T).hash_code() == typeid(float).hash_code())
            {
                for (auto &i : args.at(idx))
                {
                    ret.push_back(std::stof(i));
                }
            }
            else if (typeid(T).hash_code() == typeid(char).hash_code())
            {
                for (auto &i : args.at(idx))
                {
                    ret.push_back(i[0]);
                }
            }

            return ret;
        }

        std::vector<std::string> get_args_vector_string(std::string arg)
        {
            int idx = find_in_vector_of_vector(arg);
            if (idx == -1)
            {
                return std::vector<std::string>();
            }

            return args.at(idx);
        }

        template <typename T>
        T get_arg(std::string arg)
        {
            int idx = find_in_vector_of_vector(arg);

            if (idx == -1)
            {
                return T(-1);
            }

            if (typeid(T).hash_code() == typeid(int).hash_code())
            {
                return std::stoi(args.at(idx)[0]);
            }
            else if (typeid(T).hash_code() == typeid(float).hash_code())
            {
                return std::stof(args.at(idx)[0]);
            }
            else if (typeid(T).hash_code() == typeid(char).hash_code())
            {
                return args.at(idx)[0][0];
            }
            else if (typeid(T).hash_code() == typeid(bool).hash_code())
            {
                if (args.at(idx)[0] == "true" | args.at(idx)[0] == "yes" | args.at(idx)[0] == "1")
                {
                    return true;
                }
                else if (args.at(idx)[0] == "false" | args.at(idx)[0] == "no" | args.at(idx)[0] == "0")
                {
                    return false;
                }
            }

            return T(-1);
        }

        std::string get_arg_string(std::string arg)
        {
            int idx = find_in_vector_of_vector(arg);

            if (idx == -1)
            {
                return "";
            }

            return args.at(idx)[0];
        }
    };
}

#endif