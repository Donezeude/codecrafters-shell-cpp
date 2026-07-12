#include "type.hpp"

#include <string>
#include <filesystem>
#include <unistd.h>
#include <sstream>

namespace fs = std::filesystem;

std::string type_feature(const std::string& phrase, const std::string& path)
{
	std::stringstream path_ss(path);
	std::string dir{""};
	
	
	if(phrase == "echo"||phrase == "exit"||phrase == "type"||phrase == "pwd"||phrase == "cd")
		return phrase + " is a shell builtin";

	else
	{
		while(std::getline(path_ss, dir, ':'))
		{
			fs::path formated_dir(dir);
			fs::path phrase_path = formated_dir / phrase;

			if(access(phrase_path.c_str(), X_OK) == 0)
				return phrase + " is " + phrase_path.string();
		}
		return phrase + ": not found";
	}

}
