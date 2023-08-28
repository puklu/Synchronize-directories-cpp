#ifndef SYNCHRONIZE_HPP_
#define SYNCHRONIZE_HPP_

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <vector>

void sync(const std::string &source_path, const std::string &replica_path);

void schedule_sync(const boost::system::error_code & /*e*/,
                   boost::asio::deadline_timer *t, const std::string &src_path,
                   const std::string &replica_path, const int sync_interval);

#endif