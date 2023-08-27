#include "../include/synchronize.hpp"
#include <boost/asio.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::endl;
namespace fs = std::filesystem;

void schedule_sync(const boost::system::error_code & /*e*/,
                   boost::asio::deadline_timer *t, const std::string &src_path,
                   const std::string &replica_path, const int sync_interval) {

  // Run synchronization task
  sync(src_path, replica_path);

  // Reschedule the task after the specified interval (e.g., 10 seconds)
  t->expires_at(t->expires_at() + boost::posix_time::seconds(sync_interval));
  t->async_wait([t, src_path, replica_path,
                 sync_interval](const boost::system::error_code &error) {
    schedule_sync(error, t, src_path, replica_path, sync_interval);
  });
}

int main(int argc, char *argv[]) {
  std::map<std::string, std::string> arguments;

  arguments["-srcdir"] = "source_dir_default";
  arguments["-repdir"] = "replica_dir_default";
  arguments["-interval"] = "10";

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

  boost::asio::io_service io;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(0));

  // Schedule the initial synchronization
  schedule_sync(boost::system::error_code(), &t, arguments["-srcdir"],
                arguments["-repdir"], std::stoi(arguments["-interval"]));

  // Run the asio service
  io.run();
}