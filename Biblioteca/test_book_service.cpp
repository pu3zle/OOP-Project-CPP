#include "tests.h"

void BookServiceTester::TestAdd()
{
	BookValidator BV;
	
	std::unique_ptr<IRepo> BR = std::make_unique<BookRepo>();

	BookService BS(BR, BV);

	std::string title = "abracadabra";
	std::string author = "weltz";
	std::string genre = "history";
	int year = 1242;

	BS.Add(title, author, genre, year);
	assert(BS.GetRepo().at("Abracadabra Weltz").GetAuthor() == author);
	assert(BS.GetRepo().at("Abracadabra Weltz").GetTitle() == title);
	assert(BS.GetRepo().at("Abracadabra Weltz").GetGenre() == genre);
	assert(BS.GetRepo().at("Abracadabra Weltz").GetYear() == year);
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
	
	std::unique_ptr<IRepo> BR = std::make_unique<BookRepo>();

	
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

	std::unique_ptr<IRepo> BR = std::make_unique<BookRepo>();


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

	assert(BS.GetRepo().at("Qwe Rty").GetAuthor() == "Rty");
	assert(BS.GetRepo().at("Qwe Rty").GetTitle() == "Qwe");
	assert(BS.GetRepo().at("Qwe Rty").GetGenre() == "Action");
	assert(BS.GetRepo().at("Qwe Rty").GetYear() == 1234);

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

	std::unique_ptr<IRepo> BR = std::make_unique<BookRepo>();

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
	std::unique_ptr<IRepo> BR = std::make_unique<BookRepo>();

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
	std::unique_ptr<IRepo> BR = std::make_unique<BookRepo>();

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
	std::unique_ptr<IRepo> BR = std::make_unique<BookRepo>();

	BookValidator BV;
	BookService BS(BR, BV);

	assert(BS.GetGenres() == BS.GetGenres());

}

void BookServiceTester::TestReport()
{
	std::unique_ptr<IRepo> BR = std::make_unique<BookRepo>();

	BookValidator BV;
	BookService BS(BR, BV);

	std::string aaa = "aaa";
	std::string ggg = "ggg";
	std::string zzz = "zzz";

	std::string g1 = "action";
	std::string g2 = "action";
	std::string g3 = "history";

	BS.Add(aaa, zzz, g1, 42);
	BS.Add(aaa, ggg, g2, 34);
	BS.Add(ggg, aaa, g3, 42);

	std::vector<BookDTO> result = BS.Report();
	assert(result.at(0).getCount() == 1);
	assert(result.at(1).getCount() == 2);
	assert(result.at(1).getType() == "Action");
	assert(result.at(0).getType() == "History");

}

void BookServiceTester::TestSaveLoadRefresh()
{
	std::unique_ptr<IRepo> BFR = std::make_unique<BookFileRepo>();
	BookValidator BV;
	BookService BS(BFR, BV);
	

	std::ofstream out("from.txt");
	out << "Asd,Asd,Action,23";
	out.close();
	
	BS.SetPath("from", "txt");
	BS.Load();

	std::string title = "Asd";
	std::string author = "Asd";

	Book B("Asd", "Asd", "Action", 23);
	assert(BS.Find(title, author) == B);

	BS.SetPath("to", "txt");
	BS.Save();

	std::ifstream in("to.txt");
	std::string temp;
	in >> temp;
	assert(temp == "Asd,Asd,Action,23");
	in.close();

	system("del from.txt");
	system("del to.txt");


	std::ofstream out1("ds");
	out1 << "filename=\"asd\"\nextension=\"asd\"\n";
	out1.close();

	BS.Refresh("ds");
	assert(BS.GetRepoPath() == "asd.asd");

	system("del ds");

}

void BookServiceTester::TestUndo()
{
	std::unique_ptr<IRepo> BR = std::make_unique<BookRepo>();
	BookValidator BV;

	BookService BS(BR, BV);

	std::string asd = "asd";
	std::string qwe = "qwe";
	std::string trf = "trf";
	std::string action = "action";
	std::string horror = "horror";
	int year = 20;

	BS.Add(asd, asd, action, year);
	BS.Add(qwe, qwe, action, year);

	assert(BS.GetRepo().size() == 2);

	BS.Update(asd,asd,trf,trf,horror,21);
	
	BS.Delete(trf, trf);

	BS.Clear();

	assert(BS.GetRepo().size() == 0);
	//undo the clear
	BS.Undo();

	assert(BS.GetRepo().size() == 1);
	//undo the delete
	BS.Undo();

	assert(BS.GetRepo().size() == 2);
	//undo the update
	BS.Undo();
	
	assert(BS.GetRepo().size() == 2);
	assert(BS.Find(asd, asd).GetYear() == 20);
	//undo the add
	BS.Undo();

	assert(BS.GetRepo().size() == 1);

	BS.Undo();
	assert(BS.GetRepo().size() == 0);

	try {
		BS.Undo();
	}
	catch (const ServiceError & err)
	{
		assert(err.GetMessage() == "No more undo operations left!\n");
	}
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
	TestReport();
	TestSaveLoadRefresh();
	TestUndo();
}