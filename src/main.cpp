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
	std::string command{input.substr(0, input.find(" ")-1)};
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
		if (phrase == "echo"||phrase == "exit"||phrase == "type")
			std::cout << phrase + " is a shell builtin" << std::endl;
		
		
		else
		{
			bool broke_early = false;
			while(std::getline(path_ss, dir, ':'))
			{
				//VARIABLES
				fs::path formated_dir(dir);
			        fs::path phrase_path = formated_dir / phrase;
				//VARIABLES END

				if(access(phrase_path.c_str(), X_OK)==0)		
				{
					std::cout << phrase + " is " + phrase_path.string() << std::endl;
					broke_early = true;
					break;
				}

			}
			if(!broke_early)
				std::cerr << input.substr(input.find(" ")+1) + ": not found" << std::endl;
		}
	}
		
	else
	{
		bool broke_early = false;
		while(std::getline(path_ss, dir, ':'))
		{
			//VARIABLES
			fs::path formated_dir(dir);
			fs::path command_path = formated_dir / command;
			
			std::string command_string{command_path.string()};
			//VARIABLES END
			
			if(access(command_path.c_str(), X_OK)==0)
			{
				pid_t pid = fork();
				if(pid == 0)
				{
					char* args[] = {command_string.data(), phrase, nullptr};
					execv(command_path.c_str(), args);
				}
				else
					wait(nullptr);
			}
		}
		if(!broke_early)
	  		std::cerr << input + ": command not found" << std::endl;
	}
  }
  return 0;
}
