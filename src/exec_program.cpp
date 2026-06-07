#include "exec_program.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <sys/wait.h>
#include <filesystem>

namespace fs = std::filesystem;

void exec_program(std::string command, std::string path)
{
	std::stringstream path_ss(path);
	std::string dir{""};

	while(std::getline(path_ss, dir, ':'))
	{
		fs::path formated_dir(dir);
		fs::path command_path = formated_dir / command;

		if(access(command_path.c_str(), X_OK)==0)
			std::cout << command << std::endl;
	}
}
