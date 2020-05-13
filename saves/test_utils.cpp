#include "tests.h"

void UtilsTester::TestStringRestructuring()
{
	std::string s = "    a   b    c        ";
	StringRestructuring(s);
	assert(s == "a b c");
}
void UtilsTester::TestGetWord()
{
	std::string s = "a b c";
	unsigned int start = 0;
	std::string temp;
	temp = GetWord(s, start);
	assert(temp == "a");
	temp = GetWord(s, start);
	assert(temp == "b");
	temp = GetWord(s, start);
	assert(temp == "c");
	try {
		temp = GetWord(s, start);
		assert(false);
	}
	catch (const GeneralError&)
	{
		assert(true);
	}
}
void UtilsTester::RunAll()
{
	TestStringRestructuring();
	TestGetWord();
}