#include "../include/synchronize.hpp"
#include <filesystem>
#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::endl;
namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  std::map<std::string, std::string> arguments;

  arguments["-srcdir"] = "../source_dir_default";
  arguments["-repdir"] = "../replica_dir_default";

  for (int i = 1; i < argc; i += 2) {
    std::string arg = argv[i];
    std::string value = argv[i + 1];
    arguments[arg] = value;
  }

  // check if source directory exists
  if (!fs::exists(arguments["-srcdir"])) {
    cout << "Source directory doesnt exist! Please enter a valid path to "
            "source directory."
         << endl;
    return 1;
  }

  // make replica dir if it doesnt exist
  if (!fs::exists(arguments["-repdir"])) {
    fs::create_directory(arguments["-repdir"]);
    cout << arguments["-repdir"] << " directory created." << endl;
  }

  // for (const auto &pair : arguments) {
  //   cout << pair.first << " : " << pair.second << endl;
  // }

  sync(arguments["-srcdir"], arguments["-repdir"]);
}