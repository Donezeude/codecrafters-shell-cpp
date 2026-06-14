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

std::string double_quotes(const std::string& phrase)
{
	bool in_double{false};
	bool last_was_space{true};

	std::string result{""};

	for(char c : phrase)
	{
		if(c == '"')
			in_double = !in_double;
		
		else if(c == ' ' && !in_double)
		{
			if(!last_was_space)
				result += ' ';
			last_was_space = true;
			continue;
		}
		else
		{
			result += c;
			last_was_space = false;
		}
	}

	while(!result.empty() && result.back() == ' ')
		result.pop_back();
	
	return result;
}

std::string collapse_space(std::string& phrase)
{
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
