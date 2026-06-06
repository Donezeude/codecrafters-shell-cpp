#include <iostream>
#include <string>
#include <cstdlib> //for environment variables
#include <sstream>
#include <filesystem>

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
	std::string phrase_after{input.substr(input.find(" ")+1)};  
	std::string path{std::getenv("PATH") ? std::getenv("PATH"):""};
	std::string dir{""};

	std::stringstream path_ss(path);
	//VARIABLES END
	
	if(input == "exit")
		break;

	else if(input.find("echo") == 0)
		std::cout << phrase_after << std::endl;
	 
	else if((input.find("type") == 0) && (input.find(" ") != std::string::npos)) 
	{
		if (phrase_after == "echo"||phrase_after == "exit"||phrase_after == "type")
			std::cout << phrase_after + " is a shell builtin" << std::endl;
		
		
		else
		{
			bool broke_early = false;
			while(std::getline(path_ss, dir, ':'))
			{
				//VARIABLES
				fs::path formated_dir(dir);
			        fs::path phrase_path = formated_dir / phrase_after;
				//VARIABLES END

				if(fs::exists(phrase_path))
				{
					fs::perms p = fs::status(phrase_path).permissions();

					if((p & fs::perms::owner_exec) != fs::perms::none)
					{
						std::cout << phrase_after + " is " + phrase_path.string() << std::endl;
						broke_early = true;
						break;
					}
				}

			}
			if(!broke_early)
				std::cerr << input.substr(input.find(" ")+1) + ": not found" << std::endl;
		}
	}
		
	else
	  	std::cerr << input + ": command not found" << std::endl;
  }
  return 0;
}
