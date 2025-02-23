#ifndef _CAST_UTILS_HPP_
#define _CAST_UTILS_HPP_

#include <string>

namespace args::utils
{

bool Stob(const std::string &str);
int Stoi(const std::string &str);
long Stol(const std::string &str);
unsigned int Stoui(const std::string &str);
unsigned long Stoul(const std::string &str);
float Stof(const std::string &str);
double Stod(const std::string &str);

} // namespace args::utils

#endif // _CAST_UTILS_HPP_
