#pragma once 

#include <string>
#include <vector>


std::vector<std::string> single_tokenize(const std::string& input);

std::vector<std::string> double_tokenize(const std::string& input);

std::string exec_backslash(std::string& phrase);

pid_t exec_program(const std::string& command, std::string& input, const std::string& path);
