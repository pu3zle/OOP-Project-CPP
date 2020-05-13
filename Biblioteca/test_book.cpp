#include "tests.h"

void BookTester::TestGetters()
{
	Book a = Book();
	assert(a.GetTitle()  == "null");
	assert(a.GetAuthor() == "null");
	assert(a.GetGenre()  == "null");
	assert(a.GetYear()   ==  0);


	Book b = Book("LOTR", "Tolkien", "Adventure", 1937);
	assert(b.GetTitle() == "LOTR");
	assert(b.GetAuthor() == "Tolkien");
	assert(b.GetGenre() == "Adventure");
	assert(b.GetYear() == 1937);
}
void BookTester::TestSetters()
{
	Book b = Book("LOTR", "Tolkien", "Adventure", 1937);
	b.SetTitle("Goodbye");
	b.SetAuthor("Hemingway");
	b.SetGenre("Drama");
	b.SetYear(2000);
	assert(b.GetTitle() == "Goodbye");
	assert(b.GetAuthor() == "Hemingway");
	assert(b.GetGenre() == "Drama");
	assert(b.GetYear() == 2000);
}
void BookTester::TestCopy()
{
	Book b = Book("LOTR", "Tolkien", "Adventure", 1937);
	Book c = b;
	c = c;
	Book d = Book(b);
	assert(c.GetTitle() == "LOTR");
	assert(c.GetAuthor() == "Tolkien");
	assert(c.GetGenre() == "Adventure");
	assert(c.GetYear() == 1937);
	assert(d.GetTitle() == "LOTR");
	assert(d.GetAuthor() == "Tolkien");
	assert(d.GetGenre() == "Adventure");
	assert(d.GetYear() == 1937);
}
void BookTester::TestEqualTo()
{
	Book A = Book("abf", "ahg", "action", 1234);
	Book B = Book("asd", "asd", "action", 1234);
	Book C = Book("asd", "asd", "action", 1234);

	assert(A != B);
	assert(B == C);
}
void BookTester::TestStream()
{
	Book B = Book("a", "b", "adventure", 1234);
	std::stringstream ss;
	ss << B;

	Book A;

	ss >> A;
	assert(A.GetTitle() == "a");
	assert(A.GetAuthor() == "b");
	assert(A.GetGenre() == "adventure");
	assert(A.GetYear() == 1234);
}
void BookTester::TestBookDTO()
{
	Book A = Book("abf", "ahg", "action", 1234);
	BookDTO DTO(A.GetTitle(), A.GetGenre(), 1);
	assert(DTO.getCount() == 1);
	assert(DTO.getType() == A.GetGenre());

	BookDTO DTO2(A.GetTitle(), A.GetGenre(), 1);
	assert(DTO == DTO2);

	DTO.addTitle("asd");
	assert(DTO.getCount() == 2);

	std::stringstream ss;
	ss << DTO2;
	std::string temp;
	ss >> temp;
	assert(temp == "Type:");
	ss >> temp;
	assert(temp == "action");
	ss >> temp;
	assert(temp == ":");
	ss >> temp;
	assert(temp == "1");
	ss >> temp;
	assert(temp == "Books:");
	ss >> temp;
	assert(temp == "->");
	ss >> temp;
	assert(temp == "abf");
}
void BookTester::RunAll()
{
	TestGetters();
	TestSetters();
	TestCopy();
	TestEqualTo();
	TestStream();
	TestBookDTO();
}
