#include "../include/helpers.hpp"
#include <algorithm>
#include <boost/asio.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <openssl/sha.h>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace fs = std::filesystem;

void copyFromSource(const std::map<string, string> &files_in_source,
                    const std::map<string, string> &files_in_replica,
                    const string &source_path, const string &replica_path) {
  for (auto &file : files_in_source) {
    auto it = files_in_replica.find(file.first);
    if (it == files_in_replica.end()) {
      copyFile(file.first, source_path, replica_path);
    } else {
      if (file.second != it->second) {
        copyFile(file.first, source_path, replica_path);
      }
    }
  }
}

void deleteFromReplica(const std::map<string, string> &files_in_source,
                       const std::map<string, string> &files_in_replica,
                       const string &source_path, const string &replica_path) {
  for (auto &file : files_in_replica) {
    auto it = files_in_source.find(file.first);
    if (it == files_in_source.end()) {
      deleteFile(file.first, replica_path);
    }
  }
}

void sync(const string &source_path, const string &replica_path) {

  cout << "Synchronising...." << endl;

  std::map<string, string> files_in_source_with_hash;
  std::map<string, string> files_in_replica_with_hash;

  makeMapWithHash(files_in_source_with_hash, source_path);
  makeMapWithHash(files_in_replica_with_hash, replica_path);

  // printMapPairs(files_in_source_with_hash);
  // printMapPairs(files_in_replica_with_hash);

  copyFromSource(files_in_source_with_hash, files_in_replica_with_hash,
                 source_path, replica_path);
  deleteFromReplica(files_in_source_with_hash, files_in_replica_with_hash,
                    source_path, replica_path);
}

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
