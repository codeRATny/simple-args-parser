#ifndef _CODERATNY_ARGS_HPP_
#define _CODERATNY_ARGS_HPP_

#include <iostream>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <sstream>

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
        std::string description;
        bool аvailability = false;
        bool shackles = false;
        size_t shackle_id;
    };

    class arg_parser
    {
    private:
        std::unordered_map<int, std::vector<std::string>> args;
        std::vector<opt_struct> opts;
        std::vector<std::vector<std::string>> shackled_opts;

        int check_shackled_opts()
        {
            for (auto& i : shackled_opts)
            {
                size_t shackled_opts_size = i.size();
                uint8_t аvailability_counter = 0;

                for (auto &j : i)
                {
                    int idx = get_opt_index(j);
                    if (idx == -1)
                    {
                        std::cout << "unknown opt!\n";
                        exit(1);
                    }
                    аvailability_counter += (int)opts[idx].аvailability;
                }
                
                if (!((аvailability_counter == 0) || (аvailability_counter == shackled_opts_size)))
                {
                    std::cout << "not all shackled opts found!\n";
                    exit(1);
                }

            }
                return 0;
        }

        int get_opt_index(std::string arg)
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
                    return 0;

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

        std::string get_type_str(cdrtnrgs_type type)
        {
            switch (type)
            {
            case ARGS_TYPE_INT:
                return "INT";
            case ARGS_TYPE_FLOAT:
                return "FLOAT";
            case ARGS_TYPE_CHAR:
                return "CHAR";
            case ARGS_TYPE_STRING:
                return "STRING";
            case ARGS_TYPE_BOOL:
                return "BOOL";
            case ARGS_TYPE_VECTOR_INT:
                return "INT VECTOR";
            case ARGS_TYPE_VECTOR_FLOAT:
                return "FLOAT VECTOR";
            case ARGS_TYPE_VECTOR_CHAR:
                return "CHAR VECTOR";
            case ARGS_TYPE_VECTOR_STRING:
                return "STRING VECTOR";
            default:
                return "UNKNOWN TYPE";
            }
        }

        std::string get_necessity_str(cdrtnrgs_necessity necessity)
        {
            switch (necessity)
            {
            case ARGS_REQUIRED:
                return "REQUIRED ARGUMENT";
            case ARGS_OPTIONAL:
                return "OPTIONAL ARGUMENT";
            default:
                return "UNKNOWN";
            }
        }

        void help()
        {
            std::cout << "Opts:\n";
            for (size_t i = 0; i < opts.size(); i++)
            {
                std::stringstream shackled_with;
                for (auto &j : opts[i].opts)
                {
                    std::cout << "\t" << j << ":";

                    if (opts[i].shackles)
                    {
                        shackled_with << "\t\tshackled with:";
                        for (auto& k : shackled_opts[opts[i].shackle_id])
                        {
                            if (j != k)
                            {
                                shackled_with << " " << k;
                            }
                        }
                        shackled_with << "\n";
                    }
                }
                std::cout << " " << get_type_str(opts[i].type) << ", " << get_necessity_str(opts[i].necessity) << ", " << opts[i].description << "\n";
                std::cout << shackled_with.str();
            }
        }

    public:
        void parse(int argc, char *argv[])
        {
            if (argc > 1)
            {
                if ((!strcmp(argv[1], "-help")) | (!strcmp(argv[1], "--help")))
                {
                    help();
                    exit(1);
                }
            }

            int idx = -1;

            for (int i = 0; i < argc; i++)
            {
                if (argv[i][0] == '-')
                {
                    idx = get_opt_index(argv[i]);
                    if (idx == -1)
                    {
                        std::cout << "unrecognized args!\n";
                        exit(1);
                    }
                    opts[idx].аvailability = true;

                    continue;
                }

                if (idx != -1)
                {
                    args[idx].push_back(argv[i]);
                }
            }

            for (size_t i = 0; i < opts.size(); i++)
            {
                if (args[i].size() == 0)
                {
                    if (opts[i].necessity == ARGS_OPTIONAL)
                    {
                        continue;
                    }
                    std::cout << "empty argument "
                              << opts[i].opts[0] << "\n";
                    exit(1);
                }

                if (args.find(i) == args.end())
                {
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

            check_shackled_opts();
        }

        void set_opt(std::string opt, cdrtnrgs_necessity necessity, cdrtnrgs_type type, std::string description)
        {
            size_t idx = opts.size();
            opts.emplace_back();
            opts[idx].necessity = necessity;
            opts[idx].type = type;
            opts[idx].description = description;

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
            int idx = get_opt_index(arg);
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
            int idx = get_opt_index(arg);
            if (idx == -1)
            {
                return std::vector<std::string>();
            }

            return args.at(idx);
        }

        template <typename T>
        T get_arg(std::string arg)
        {
            int idx = get_opt_index(arg);

            if ((idx == -1))
            {
                std::cout << "unknown opt!\n";
                exit(1); // temp
            }

            if (typeid(T).hash_code() == typeid(int).hash_code())
            {
                if (args.at(idx).size() == 0)
                {
                    return -1;
                }
                return std::stoi(args.at(idx)[0]);
            }
            else if (typeid(T).hash_code() == typeid(float).hash_code())
            {
                if (args.at(idx).size() == 0)
                {
                    return -1;
                }
                return std::stof(args.at(idx)[0]);
            }
            else if (typeid(T).hash_code() == typeid(char).hash_code())
            {
                if (args.at(idx).size() == 0)
                {
                    return -1;
                }
                return args.at(idx)[0][0];
            }
            else if (typeid(T).hash_code() == typeid(bool).hash_code())
            {
                return opts[idx].аvailability;
            }

            return T(-1);
        }

        std::string get_arg_string(std::string arg)
        {
            int idx = get_opt_index(arg);

            if (idx == -1)
            {
                return "";
            }

            if (args.at(idx).size() == 0)
            {
                return "";
            }

            return args.at(idx)[0];
        }

        int shackle_opts(std::vector<std::string> b)
        {
            for (auto &i : b)
            {
                int idx = get_opt_index(i);
                if (idx == -1)
                {
                    std::cout << "unknown opt!\n";
                    exit(1);
                }
                opts[idx].shackles = true;
                opts[idx].shackle_id = shackled_opts.size();
            }
            shackled_opts.push_back(b);

            return 0;
        }
    };
}

#endif