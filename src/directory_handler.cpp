#include "../include/constants.hpp"
#include <filesystem>
#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::endl;
namespace fs = std::filesystem;

void displayDirectoriesBeingUsed(
    const std::map<std::string, std::string> &arguments) {

  if (arguments.at("-srcdir") == SOURCE_DIR_DEFAULT) {
    cout << "    #Source directory not provided, using the default source "
            "directory."
         << endl;
  } else {
    cout << "    #Source directory: " << arguments.at("-srcdir") << endl;
  }

  if (arguments.at("-repdir") == REPLICA_DIR_DEFAULT) {
    cout << "    #Replica directory not provided, using the default replica "
            "directory."
         << endl;
  } else {
    cout << "    #Replica directory: " << arguments.at("-repdir") << endl;
  }

  cout << "    #Synchronising at an interval of " << arguments.at("-interval")
       << " secs.\n"
       << endl;
}

void checkIfSourceDirectoryValid(
    const std::map<std::string, std::string> &arguments) {
  if (!fs::exists(arguments.at("-srcdir"))) {
    cout << "Source directory doesnt exist! Please enter a valid path to "
            "source directory."
         << endl;
    exit(1);
  }
}

void createReplicaDirectoryIfNotExists(
    const std::map<std::string, std::string> &arguments) {
  if (!fs::exists(arguments.at("-repdir"))) {
    fs::create_directory(arguments.at("-repdir"));
    cout << arguments.at("-repdir") << " directory created." << endl;
  }
}
