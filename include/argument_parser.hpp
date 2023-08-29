#ifndef ARGUMENT_PARSER_HPP
#define ARGUMENT_PARSER_HPP

#include <map>
#include <string>

std::map<std::string, std::string> parseArguments(int argc, char *argv[]);

#endif // ARGUMENT_PARSER_HPP