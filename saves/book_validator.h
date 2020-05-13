#pragma once
#include "utilities.h"
#include "book.h"

class ValidatorError : public GeneralError {
public:
	ValidatorError(std::string message) : GeneralError(message) {}
};

class BookValidator {
private:
	std::list<std::string> genres = {
		"action", "adventure", "horror", "thriller","comedy",
		"drama","mystery","crime","history","fantasy","poetry",
		"romance","sf","suspense","health","science","travel",
		"biography","autobiography","art","diary","encyclopedia"
	};
public:
	BookValidator(){}
	/*
		Params: an int
		Returns: true - if the integer is a valid year ( greater than 0 and lower than 2021)
		Throws: ValidatorError - if the integer is not a valid year ( lower than 1 and greater than 2020 )
	*/
	bool ValidateYear(int);
	/*
		Params: a string
		Returns: true - if the string is a valid genre (found in the private attribute <genres>)
		Throws: ValidatorError - if the string is not a valid genre (not found in the private attribute <genres>)
	*/
	bool ValidateGenre(std::string);
	/*
		Params: a string
		Returns: true - if the string is not empty
		Throws: ValidatorError - if the string is empty
	*/
	bool ValidateString(const std::string&);
	/*
		Params: a book
		Returns: true - if the book is valid (valid title, valid genre, valid author, valid year)
		Throws: ValidatorError - if the book is not valid
	*/
	bool ValidateBook(const Book&);
	/*
		The function return a const reference to the list of genres
	*/
	const std::list<std::string>& GetGenres() { return genres; }
	~BookValidator() = default;
};