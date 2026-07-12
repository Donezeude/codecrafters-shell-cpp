#include "cd.hpp"

#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

fs::path change_dir(const std::string& phrase)
{
	const char* user = std::getenv("HOME"); //Linux/Mac
	if (!user) user = std::getenv("USERPROFILE"); //Windows fallback
	if(phrase == "~")
		return fs::path("/home") / user;

	else if(phrase == "../"||phrase == "..")
		return fs::canonical(fs::current_path() / phrase);
	
	else if(phrase == ".")
		return fs::current_path();
	
	else if(fs::exists(phrase))
		return fs::path(phrase);

	else
		return fs::path{};
}
