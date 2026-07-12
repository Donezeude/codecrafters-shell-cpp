#include "exec_program.hpp"

#include <string>
#include <sstream>
#include <sys/wait.h>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;


std::vector<std::string> double_tokenize(const std::string& input)
{
	std::vector<std::string> elements;
	std::string current;
	bool in_quote{false};

	for(char c : input)
	{
		if(c == '"')
			in_quote = !in_quote;

		else if(c == ' ' && in_quote == false)
		{
			if(!current.empty())
			{
				elements.push_back(current);
				current.clear();
			}
		}
		else
			current += c;
	}
	if(!current.empty())
		elements.push_back(current);
	
	return elements;
}

std::vector<std::string> single_tokenize(const std::string& input)
{
	std::vector<std::string> elements;
	std::string current;
	bool in_quote{false};

	for (char c : input)
	{
		if(c == '\'')
			in_quote = !in_quote;
		else if(c == ' ' && in_quote == false) //if one quoted phrase is done and there is a gap
		{
			if(!current.empty())
			{
				elements.push_back(current);
				current.clear();
			}
		}
		else
			current += c;
	}
	if(!current.empty())
		elements.push_back(current);

	return elements;
}

std::string exec_backslash(std::string& phrase)
{
	std::string result;
	result.reserve(phrase.size());

	for(size_t i=0; i < phrase.size(); i++)
	{
		if(phrase[i] == '\\' && i + 1 < phrase.size())
		{
			char next = phrase[i+1];
			if(next == '\\')
			{
				result += '\\';
				++i;
			}
			else
			{
				result += next;
				++i;
			}	
		}
		else
			result += phrase[i];
	}
	phrase = result;
	return phrase;
}





pid_t exec_program(const std::string& command, std::string& input, const std::string& path)
{
	std::stringstream path_ss(path);
	std::string dir{""};

	std::vector<std::string> elements;
	std::string el{""};

	while(std::getline(path_ss, dir, ':'))
	{
		fs::path formated_dir(dir);
		fs::path command_path = formated_dir / command;

		if(access(command_path.c_str(), X_OK)==0)
		{
			std::stringstream input_ss(exec_backslash(input));
			
			std::vector<char*> args;
			std::vector<std::string> elements;
			std::string el{""};

			if(input.find('"') != std::string::npos)
				elements = double_tokenize(input);

			else if(input.find('\'') != std::string::npos)
				elements = single_tokenize(input);
			else
			{
				while(std::getline(input_ss, el, ' '))
					elements.push_back(el);
			}

			
			for(std::string& e : elements)
				args.push_back(e.data());
			args.push_back(nullptr);

			pid_t pid = fork();
			if(pid == 0)
				execv(command_path.c_str(), args.data());
			else
				return wait(nullptr);
		}
	}
	return -1;
}
