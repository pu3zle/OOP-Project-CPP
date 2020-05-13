#include "book_validator.h"

bool BookValidator::ValidateYear(int year)
{
	if (year <= 0)
		throw ValidatorError("Year must be greater than 0!\n");
	if (year > 2020)
		throw ValidatorError("Year can't be greater than 2020!\n");
	return true;
}

bool BookValidator::ValidateGenre(std::string genre)
{
	//I could have just used ::tolower instead of a lambda, but I was getting
	//a warning "conversion from int to char" from the transform function
	std::transform(genre.begin(), genre.end(), genre.begin(), [](int c) noexcept -> char { return static_cast<char>(::tolower(c)); });
	auto it = std::find(genres.begin(), genres.end(), genre);
	if (it == genres.end())
		throw ValidatorError("The library doesn't recognize this book genre!\n");
	return true;
}

bool BookValidator::ValidateString(const std::string& s)
{
	if (s.empty())
		throw ValidatorError("String cannot be empty!\n");
	return true;
}

bool BookValidator::ValidateBook(const Book& book)
{
	std::string errors = "";

	if (book.GetAuthor().empty())
		errors += "String cannot be empty!\n";
	if(book.GetTitle().empty())
		errors += "String cannot be empty!\n";
	try
	{
		ValidateGenre(book.GetGenre());
	}
	catch (const ValidatorError & error)
	{
		errors += error.GetMessage();
	}

	if (book.GetYear() <= 0)
		errors += "Year must be greater than 0!\n";
	else if (book.GetYear() > 2020)
		errors += "Year can't be greater than 2020!\n";
	
	if (!errors.empty())
		throw ValidatorError(errors);
	return true;
}
