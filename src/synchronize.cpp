#include "../include/helpers.hpp"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace fs = std::filesystem;

vector<string> makeVector(const string &directory_path) {
  vector<string> result;
  for (const auto &file : fs::directory_iterator(directory_path)) {
    result.push_back(file.path().filename().string());
  }
  return result;
}

void sync(const string &source_path, const string &replica_path) {

  vector<string> files_in_source = makeVector(source_path);
  vector<string> files_in_replica = makeVector(replica_path);

  for (string file : files_in_source) {
    auto it = std::find(files_in_replica.begin(), files_in_replica.end(), file);
    if (it == files_in_replica.end()) {
      copyFile(file, source_path, replica_path);
    }
  }

  //   for (const auto &file : fs::directory_iterator(source_path)) {
  // copyFile(file.path(), replica_path);
  //   }
}