#include "tests.h"

void BookValidatorTester::TestValidateYear()
{
	try
	{
		DummyValidator.ValidateYear(-2);
		assert(false);
	}
	catch (const ValidatorError& error)
	{
		assert(error.GetMessage() == "Year must be greater than 0!\n");
	}

	try
	{
		DummyValidator.ValidateYear(2021);
		assert(false);
	}
	catch (const ValidatorError & error)
	{
		assert(error.GetMessage() == "Year can't be greater than 2020!\n");
	}

	assert(DummyValidator.ValidateYear(1999) == true);
}
void BookValidatorTester::TestValidateGenre()
{
	try
	{
		DummyValidator.ValidateGenre("aezakmi");
		assert(false);
	}
	catch (const ValidatorError & error)
	{
		assert(error.GetMessage() == "The library doesn't recognize this book genre!\n");
	}

	assert(DummyValidator.ValidateGenre("comedy") == true);
}
void BookValidatorTester::TestValidateString()
{
	std::string s = "asd";
	assert(DummyValidator.ValidateString(s) == true);

	s = "";
	try {
		DummyValidator.ValidateString(s);
		assert(false);
	}
	catch (const ValidatorError & error)
	{
		assert(error.GetMessage() == "String cannot be empty!\n");
	}
	
}
void BookValidatorTester::TestValidateBook()
{
	Book b = Book("asd", "asd", "action", 2000);
	assert(DummyValidator.ValidateBook(b) == true);

	b = Book("", "", "asd", -1333);
	try
	{
		DummyValidator.ValidateBook(b);
		assert(false);
	}
	catch (const ValidatorError & error){
		assert(error.GetMessage() == "String cannot be empty!\nString cannot be empty!\nThe library doesn't recognize this book genre!\nYear must be greater than 0!\n");
	}
	b.SetYear(2021);
	try
	{
		DummyValidator.ValidateBook(b);
		assert(false);
	}
	catch (const ValidatorError & error) {
		assert(error.GetMessage() == "String cannot be empty!\nString cannot be empty!\nThe library doesn't recognize this book genre!\nYear can't be greater than 2020!\n");
	}
}
void BookValidatorTester::RunAll()
{
	TestValidateYear();
	TestValidateGenre();
	TestValidateString();
	TestValidateBook();
}