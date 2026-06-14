#include "echo.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

std::string single_quotes(std::string& phrase) 
{
	phrase.erase(std::remove(phrase.begin(), phrase.end(), '\''), phrase.end());

	return phrase;
}


std::string double_quotes(std::string& phrase)
{
	phrase.erase(std::remove(phrase.begin(), phrase.end(), '\"'), phrase.end());
	return phrase;

std::string collapse_space(std::string& phrase)
{
	phrase = double_quotes(phrase);

	std::stringstream phrase_ss{phrase};

	std::string result{""};
	std::string word{""};

	while(phrase_ss >> word)
	{
		if(!result.empty())
			result += " ";
		result += word;
	}
	return result;
}
