#include "tests.h"

void CartTester::TestAdd()
{
	CartRepo CR;
	BookValidator BV;
	CartService CS(CR, BV);

	std::unique_ptr<IRepo> BR = std::make_unique<BookRepo>();

	BookService BS(BR, BV);

	std::string title = "asd";
	std::string author = "asd";
	std::string genre = "action";
	int year = 2000;

	BS.Add(title, author, genre, year);

	CS.Add(title, author, BS.GetRepo());
	CS.Add(title, author, BS.GetRepo());

	assert(CS.GetCart().qsize() == 2);


}
void CartTester::TestRandom()
{
	CartRepo CR;
	BookValidator BV;
	CartService CS(CR, BV);

	std::unique_ptr<IRepo> BR = std::make_unique<BookRepo>();

	BookService BS(BR, BV);

	std::string title = "asd";
	std::string author = "asd";
	std::string genre = "action";
	int year = 2000;

	try {
		CS.GenerateCart(3, BS.GetRepo());
	}
	catch (const RepoError&) {}

	BS.Add(title, author, genre, year);

	CS.GenerateCart(3, BS.GetRepo());

	assert(CS.GetCart().qsize() == 3);

}
void CartTester::TestClear()
{
	CartRepo CR;
	BookValidator BV;
	CartService CS(CR, BV);
	std::unique_ptr<IRepo> BR = std::make_unique<BookRepo>();

	BookService BS(BR, BV);

	std::string title = "asd";
	std::string author = "asd";
	std::string genre = "action";
	int year = 2000;

	BS.Add(title, author, genre, year);

	CS.GenerateCart(3, BS.GetRepo());

	assert(CS.GetCart().qsize() == 3);

	CS.Clear();

	assert(CS.GetCart().empty());

}
void CartTester::TestSave()
{
	CartRepo CR;
	BookValidator BV;
	CartService CS(CR, BV);

	std::unique_ptr<IRepo> BR = std::make_unique<BookRepo>();

	BookService BS(BR, BV);

	std::string title = "asd";
	std::string author = "asd";
	std::string genre = "action";
	int year = 2000;

	std::string filename = "test";
	std::string extension = "csv";
	
	try
	{ 
		CS.Save(filename, extension);
	}
	catch (const GeneralError&) {}

	BS.Add(title, author, genre, year);

	CS.GenerateCart(2, BS.GetRepo());

	CS.Save(filename, extension);

	std::ifstream in1("test.csv");
	std::string line;
	int count = -1; //getline will make one extra step and realize there's nothing to read
	while (std::getline(in1, line))
	{
		count++;
	}
	assert(count == 2);

	in1.close();

	extension = "html";
	CS.Save(filename, extension);

	std::ifstream in2("test.html");
	count = -1;
	while (std::getline(in2, line))
	{
		count++;
	}
	assert(count == 0);
	//in html there is no '\n', we have <br> therefore, only one line read

	in2.close();

	extension = "fail";
	try
	{
		CS.Save(filename, extension);
	}
	catch (const GeneralError&) {}

	system("del test.html");
	system("del test.csv");
}

void CartTester::RunAll()
{
	TestAdd();
	TestRandom();
	TestClear();
	TestSave();
}