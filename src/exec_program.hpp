#pragma once 

#include <string>

pid_t exec_program(const std::string& command, std::string& input, const std::string& path);
