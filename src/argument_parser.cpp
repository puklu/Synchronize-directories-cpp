#include "../include/constants.hpp"
#include <iostream>
#include <map>
#include <string>

void displayUsage() {
  std::cout << "Usage: ./main [-srcdir source_dir] [-repdir "
               "replica_dir] [-interval sync_interval]"
            << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -srcdir         Specify the source directory" << std::endl;
  std::cout << "  -repdir         Specify the replica directory" << std::endl;
  std::cout
      << "  -interval       Specify the synchronization interval (in seconds)"
      << std::endl;
}

std::map<std::string, std::string> parseArguments(int argc, char *argv[]) {

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-h" || arg == "--help") {
      displayUsage();
      exit(1);
    }
  }

  if ((argc - 1) % 2 != 0) {
    std::cout << "Invalid number of arguments. Use -h or --help for usage."
              << std::endl;
    exit(1);
  }

  std::map<std::string, std::string> arguments;

  arguments["-srcdir"] = SOURCE_DIR_DEFAULT;
  arguments["-repdir"] = REPLICA_DIR_DEFAULT;
  arguments["-interval"] = SYNC_INTERVAL_DEFAULT;

  for (int i = 1; i < argc; i += 2) {
    std::string arg = argv[i];
    std::string value = argv[i + 1];
    arguments[arg] = value;
  }

  return arguments;
}
