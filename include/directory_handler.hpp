#ifndef DIRECTORY_HANDLER_HPP
#define DIRECTORY_HANDLER_HPP

#include <map>
#include <string>

void displayDirectoriesBeingUsed(
    const std::map<std::string, std::string> &arguments);
void checkIfSourceDirectoryValid(
    const std::map<std::string, std::string> &arguments);
void createReplicaDirectoryIfNotExists(
    const std::map<std::string, std::string> &arguments);

#endif // DIRECTORY_HANDLER_HPP