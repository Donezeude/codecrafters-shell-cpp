#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;


  while(true) 
  {
	  std::cout << "$ ";

	  std::string input{""};	  
	  std::getline(std::cin, input);
	  
	  if(input == "exit")
	  	break;

	  else if(input.find("echo") == 0)
		std::cout << input.substr(input.find(" ")+1) << std::endl;
	 
	  else if((input.find("type") == 0) &&
		  (input.find(" ") != std::string::npos) &&
	          (input.substr(input.find(" ")+1) == "echo"||
		   input.substr(input.find(" ")+1) == "exit"||
		   input.substr(input.find(" ")+1) == "type"))
		std::cout << input.substr(input.find(" ")+1) + " is a shell builtin" << std::endl;

		

	  else
	  	std::cerr << input + ": command not found" << std::endl;
  }
  return 0;
}
