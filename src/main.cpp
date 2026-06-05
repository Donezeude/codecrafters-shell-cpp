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

	  else
	  	std::cerr << input + ": command not found" << std::endl;
  }
  return 0;
}
