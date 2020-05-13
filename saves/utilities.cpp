#include "utilities.h"

void StringCapitalize(std::string& any_string)
{
	if (any_string.empty())
		return;
	any_string[0] = static_cast<char>(std::toupper(any_string.at(0)));
}

void StringRestructuring(std::string& any_string)
{
	std::stringstream ss;
	ss << any_string;
	any_string.clear();
	std::string temp;
	while (ss >> temp)
		any_string += temp + " ";
	any_string.pop_back();
}

std::string GetWord(std::string& s, unsigned int& start)
{
	if (start >= s.size())
		throw GeneralError("Invalid start position!\n");
	std::string result;
	for (unsigned int i = start; i < s.size(); i++)
	{
		if (s[i] != ' ')
			result += s[i];
		else {
			start = i + 1;
			return result;
		}
	}
	start = s.size();
	return result;
}
