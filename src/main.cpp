#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::cout << "$ ";
	
  std::string input = "";
  std::getline(std::cin, input);
	
  std::string error_msg = input + ": command not found";
  std::cerr << error_msg << "\n";
}
