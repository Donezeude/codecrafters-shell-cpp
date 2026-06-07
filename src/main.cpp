#include "type.hpp"
#include "exec_program.hpp"

#include <iostream>
#include <string>
#include <cstdlib> //for environment variables
#include <sstream>
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
	std::string dir{""};

	std::stringstream path_ss(path);
	//VARIABLES END
	
	if(input == "exit")
		break;

	else if(input.find("echo") == 0)
		std::cout << phrase << std::endl;
	 
	else if((input.find("type") == 0) && (input.find(" ") != std::string::npos)) 
	{
		std::string result{type_feature(phrase,path)};

		if(result.find(": not found") != std::string::npos)
			std::cerr << result << std::endl;
		else
			std::cout << result << std::endl;
	}
		
	else
	{
	  	exec_program(command, path);
	}
  }
  return 0;
}
