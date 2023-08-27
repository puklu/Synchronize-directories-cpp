#include <filesystem>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

namespace fs = std::filesystem;

void copyFile(const std::string &filename, const std::string &fromWhere,
              const std::string &toWhere) {
  std::string filepath_in_source = fromWhere + "/" + filename;
  std::string filepath_in_replica = toWhere + "/" + filename;

  try {
    // if (!fs::exists(filepath_in_replica)) {
    fs::copy_file(filepath_in_source, filepath_in_replica);
    cout << filename << " copied to " << toWhere << endl;
    // }
  } catch (const fs::filesystem_error &e) {
    cerr << e.what() << endl;
  }
}