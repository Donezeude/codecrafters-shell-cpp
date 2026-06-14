#pragma once 

#include <string>
#include <vector>

std::vector<std::string> tokenize(const std::string& input);
pid_t exec_program(const std::string& command, std::string& input, const std::string& path);
