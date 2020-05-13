#include "tests.h"

void BookServiceTester::TestAdd()
{
	BookValidator BV;
	BookRepo BR;
	BookService BS(BR, BV);

	std::string title = "abracadabra";
	std::string author = "weltz";
	std::string genre = "history";
	int year = 1242;

	BS.Add(title, author, genre, year);
	assert(BS.GetRepo().at(0).GetAuthor() == author);
	assert(BS.GetRepo().at(0).GetTitle() == title);
	assert(BS.GetRepo().at(0).GetGenre() == genre);
	assert(BS.GetRepo().at(0).GetYear() == year);
	assert(BS.GetRepo().size() == 1);


	title = "";
	author = "asd";
	genre = "asd";
	year = -1;
	try {
		BS.Add(title, author, genre, year);
		assert(false);
	}
	catch (const ValidatorError & err)
	{
		assert(err.GetMessage() == "String cannot be empty!\nThe library doesn't recognize this book genre!\nYear must be greater than 0!\n");
	}

}
void BookServiceTester::TestGet()
{
	BookValidator BV;
	BookRepo BR;
	BookService BS(BR, BV);

	std::string title = "Abracadabra";
	std::string author = "Weltz";
	std::string genre = "History";
	constexpr int year = 1242;

	Book A = Book(title, author, genre, year);

	BS.Add(title, author, genre, year);
	assert(BS.Find(title, author) == A);

	title = "asd";
	try {
		Book B = BS.Find(title, author);
		assert(false);
	}
	catch (const RepoError & err)
	{
		assert(err.GetMessage() == "Inexisting element!\n");
	}
	
}
void BookServiceTester::TestUpdate()
{
	BookRepo BR;
	BookValidator BV;
	BookService BS(BR, BV);

	std::string TitleToFind = "asd";
	std::string AuthorToFind = "asd";
	std::string GenreToFind = "adventure";

	std::string UpdatedTitle = "qwe";
	std::string UpdatedAuthor = "rty";
	std::string UpdatedGenre = "action";
	constexpr int UpdatedYear = 1234;
	BS.Add(TitleToFind, AuthorToFind, GenreToFind, 123);
	BS.Update(TitleToFind, AuthorToFind, UpdatedTitle, UpdatedAuthor, UpdatedGenre, UpdatedYear);

	assert(BS.GetRepo().at(0).GetAuthor() == "Rty");
	assert(BS.GetRepo().at(0).GetTitle() == "Qwe");
	assert(BS.GetRepo().at(0).GetGenre() == "Action");
	assert(BS.GetRepo().at(0).GetYear() == 1234);

	try {
		TitleToFind = "tyr";
		BS.Update(TitleToFind, AuthorToFind, UpdatedTitle, UpdatedAuthor, UpdatedGenre, UpdatedYear);
		assert(false);
	}
	catch(const RepoError& err){
		assert(err.GetMessage() == "Inexisting element!\n");
	}

}
void BookServiceTester::TestDelete()
{
	BookValidator BV;
	BookRepo BR;
	BookService BS(BR, BV);

	std::string title = "abracadabra";
	std::string author = "weltz";
	std::string genre = "history";
	constexpr int year = 1242;



	try {
		Book B = BS.Delete(title, author);
		assert(false);
	}
	catch(const RepoError& err){
		assert(err.GetMessage() == "Inexisting element!\n");
	}
	BS.Add(title, author, genre, year);

	StringCapitalize(title);
	StringCapitalize(author);
	StringCapitalize(genre);

	Book A = Book(title, author, genre, year);
	Book B = BS.Delete(title, author);

	assert(B == A);
	assert(B.GetGenre() == A.GetGenre());
	assert(B.GetYear() == A.GetYear());
}

void BookServiceTester::TestSort()
{
	BookRepo BR;
	BookValidator BV;
	BookService BS(BR, BV);
	
	std::string aaa = "aaa";
	std::string ggg = "ggg";
	std::string zzz = "zzz";

	std::string g1 = "action";
	std::string g2 = "comedy";
	std::string g3 = "history";

	BS.Add(aaa, zzz, g1, 42);
	BS.Add(zzz, ggg, g2, 34);
	BS.Add(ggg, aaa, g3, 14);

	auto result = BS.Sort(1);
	assert(result.at(0).GetTitle() == "Aaa");
	assert(result.at(1).GetTitle() == "Ggg");
	assert(result.at(2).GetTitle() == "Zzz");

	result = BS.Sort(2);
	assert(result.at(0).GetAuthor() == "Aaa");
	assert(result.at(1).GetAuthor() == "Ggg");
	assert(result.at(2).GetAuthor() == "Zzz");

	result = BS.Sort(3);
	assert(result.at(0).GetGenre() == "Action");
	assert(result.at(1).GetGenre() == "Comedy");
	assert(result.at(2).GetGenre() == "History");

	result = BS.Sort(4);
	assert(result.at(0).GetYear() == 14);
	assert(result.at(1).GetYear() == 34);
	assert(result.at(2).GetYear() == 42);
}
void BookServiceTester::TestFilter()
{
	BookRepo BR;
	BookValidator BV;
	BookService BS(BR, BV);

	std::string aaa = "aaa";
	std::string ggg = "ggg";
	std::string zzz = "zzz";

	std::string g1 = "action";
	std::string g2 = "comedy";
	std::string g3 = "history";

	std::string year = "42";

	BS.Add(aaa, zzz, g1, 42);
	BS.Add(aaa, ggg, g2, 34);
	BS.Add(ggg, aaa, g3, 42);

	auto result = BS.Filter(aaa);
	assert(result.at(0).GetTitle() == "Aaa");
	assert(result.at(1).GetTitle() == "Aaa");

	result = BS.Filter(year);
	assert(result.at(0).GetYear() == 42);
	assert(result.at(1).GetYear() == 42);

}
void BookServiceTester::TestGetGenres()
{
	BookRepo BR;
	BookValidator BV;
	BookService BS(BR, BV);

	assert(BS.GetGenres() == BS.GetGenres());
}


void BookServiceTester::RunAll()
{
	TestAdd();
	TestGet();
	TestUpdate();
	TestDelete();
	TestSort();
	TestFilter();
	TestGetGenres();

}