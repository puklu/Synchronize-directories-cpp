#ifndef HELPERS_HPP_
#define HELPERS_HPP_

#include <filesystem>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace fs = std::filesystem;

void copyFile(const std::string &filename, const std::string &fromWhere,
              const std::string &toWhere);

void deleteFile(const std::string &filename, const std::string &fromWhere);

std::string calculateMD5(const std::string &filename);

void makeMapWithHash(std::map<std::string, std::string> &mapWithHash,
                     const std::string &directory_path,
                     const std::string &current_relative_path = "");

std::vector<std::string> makeVector(const std::string &directory_path);

void printStringVector(const std::vector<std::string> vec);

void printMapPairs(const std::map<std::string, std::string> myMap);

#endif