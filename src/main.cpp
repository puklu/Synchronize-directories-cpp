#include "../include/argument_parser.hpp"
#include "../include/constants.hpp"
#include "../include/directory_handler.hpp"
#include "../include/loggers.hpp"
#include "../include/synchronize.hpp"
#include <filesystem>
#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::endl;
namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  std::map<std::string, std::string> arguments = parseArguments(argc, argv);

  welcomeMessage();

  checkIfSourceDirectoryValid(arguments);

  displayDirectoriesBeingUsed(arguments);

  createReplicaDirectoryIfNotExists(arguments);

  boost::asio::io_service io;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(0));

  // Schedule the initial synchronization
  schedule_sync(boost::system::error_code(), &t, arguments["-srcdir"],
                arguments["-repdir"], std::stoi(arguments["-interval"]));

  // Run the asio service
  io.run();
}