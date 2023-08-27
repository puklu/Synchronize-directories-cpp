#ifndef HELPERS_HPP_
#define HELPERS_HPP_

#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

void copyFile(const std::string &filename, const std::string &fromWhere,
              const std::string &toWhere);

#endif