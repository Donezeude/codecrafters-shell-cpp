#include "echo.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>


std::string quotes(const std::string& phrase)
{
	bool in_double{false};
	bool in_single{false};
	bool last_was_space{true};

	std::string result{""};

	for(char c : phrase)
	{
		if(c == '"')
			in_double = !in_double;
		
		else if(c == '\'')
			in_single = !in_single;

		else if(c == ' ' && !in_double && !in_single)
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
