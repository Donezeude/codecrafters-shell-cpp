#include "minors/type.hpp"
#include "minors/exec_program.hpp"
#include "minors/cd.hpp"
#include "minors/echo.hpp"


#include <iostream>
#include <string>
#include <cstdlib> //for environment variables
#include <filesystem>
#include <unistd.h>
#include <sys/wait.h>

namespace fs = std::filesystem;

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;


  while(true) 
  {
	std::cout << "$ ";

	std::string input{""};	  
	std::getline(std::cin, input);
	 
	//VARIABLES
	std::string command{input.substr(0, input.find(" "))};
	std::string phrase{input.substr(input.find(" ")+1)};  
	std::string path{std::getenv("PATH") ? std::getenv("PATH"):""};
	//VARIABLES END

	if(input.empty())
		continue;

	if(input == "exit")
		break;

	else if(input.find("echo") == 0)
	{
		size_t find_backslash = phrase.find('\\');
		size_t find_double    = phrase.find('"');
		size_t find_single    = phrase.find('\'');

		if(find_backslash != std::string::npos || find_double != std::string::npos || find_single != std::string::npos)
		{
			if(find_backslash < find_single || find_double < find_single)
				std::cout << backslash(phrase) << std::endl;

			else if(find_double  != std::string::npos && 
				    (find_single == std::string::npos || find_double < find_single))
				std::cout << double_quotes(phrase) << std::endl;

			else
				std::cout << single_quotes(phrase) << std::endl;
		}
		
		else
			std::cout << collapse_space(phrase) << std::endl;
	}

	else if(input.find("pwd") == 0)
		std::cout << fs::current_path().string() << std::endl;

	else if((input.find("type") == 0) && (input.find(" ") != std::string::npos)) 
	{
		std::string result{type_feature(phrase,path)};

		if(result.find(": not found") != std::string::npos)
			std::cerr << result << std::endl;
		else
			std::cout << result << std::endl;
	}
	
	else if(input.find("cd") == 0) 
	{
		fs::path result{change_dir(phrase)};

		if(result.empty())
			std::cerr << "cd: " + phrase + ": No such file or directory" << std::endl;
		else
			fs::current_path(result);
	}

	else
	{
	  	if(exec_program(command, input, path) == -1)
			std::cerr << input + ": command not found" << std::endl;
	}
  }
  return 0;
}
