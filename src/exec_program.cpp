#include "exec_program.hpp"
#include "echo.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <sys/wait.h>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

pid_t exec_program(const std::string& command, std::string& input, const std::string& path)
{
	std::stringstream path_ss(path);
	std::string dir{""};

	std::vector<std::string> elements;
	std::string el{""};

	while(std::getline(path_ss, dir, ':'))
	{
		fs::path formated_dir(dir);
		fs::path command_path = formated_dir / command;

		if(access(command_path.c_str(), X_OK)==0)
		{
			std::stringstream input_ss(input);
			
			std::vector<char*> args;
			std::vector<std::string> elements;
			std::string el{""};


			while(std::getline(input_ss, el, '\''))
				elements.push_back(el);

			for(const auto& tim : elements)
			{ std::cout << tim << "      "; }
			std::cout << std::endl;
			
			for(std::string& e : elements)
				args.push_back(e.data());
			args.push_back(nullptr);

			pid_t pid = fork();
			if(pid == 0)
				execv(command_path.c_str(), args.data());
			else
				return wait(nullptr);
		}
	}
	return -1;
}
