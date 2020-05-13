#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <list>
#include <unordered_map>

//Exceptie 
class GeneralError {
private:
	const std::string message;
public:
	GeneralError(std::string message) : message(message) {}
	const std::string& GetMessage() const noexcept {
		return message;
	}
};
/*
	Params: a reference to a string
	Details: The function capitalizes the first letter of the string
*/
void StringCapitalize(std::string&);
/*
	Params: a reference to a string
	Details: The function eliminates the unnecessary spaces from a string
*/
void StringRestructuring(std::string& any_string);
/*
	Params: a reference to a string, a reference to an uint
	Returns: a string representing the first word occured, starting from the uint "start"
	Throws: GeneralError - if there are no more words to be extracted from the given string
*/
std::string GetWord(std::string&, unsigned int& start);