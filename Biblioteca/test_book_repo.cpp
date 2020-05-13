#include "tests.h"

void BookRepoTester::TestStore()
{
	BookRepo BR;


	Book A = Book("afd", "asd", "history", 1234);
	Book B = Book("agd", "asd", "history", 1234);
	Book C = Book("asd", "asd", "history", 1234);

	BR.store(A);
	assert(BR["afd asd"] == A);
	assert(BR.size() == 1);
	try
	{
		BR.store(A);
		assert(false);
	}
	catch (const RepoError & error)
	{
		assert(error.GetMessage() == "Already existing element!\n");
	}
	assert(BR.at("afd asd") == A);
	assert(BR.size() == 1);

	BR.store(B);
	BR.store(C);

	auto elems = BR.GetReference();

	assert(elems[0] == A);
	assert(elems.at(1) == B);
	assert(BR["asd asd"] == C);
	assert(BR.size() == 3);

	BR.clear();
	assert(BR.empty() == true);

}
void BookRepoTester::TestGet()
{
	BookRepo BR;
	Book A = Book("asd", "asd", "action", 1234);
	Book B = Book("awd", "asd", "action", 1234);
	Book C = Book("add", "asd", "action", 1234);
	
	BR.store(A);
	BR.store(B);
	BR.store(C);

	Book KeyA = Book("asd", "asd", "", 0);
	Book KeyB = Book("awd", "asd", "", 0);
	Book KeyC = Book("add", "asd", "", 0);

	assert(BR.get(KeyA) == A);
	assert(BR.get(KeyB) == B);
	assert(BR.get(KeyC) == C);

	Book InexistingKey = Book("inexisting", "not here", "i'm serious", 1337);
	try {
		BR.get(InexistingKey);
		assert(false);
	}
	catch (const RepoError & error)
	{
		assert(error.GetMessage() == "Inexisting element!\n");
	}

	const BookRepo CBR(BR);
	assert(BR["asd asd"] == A);

}
void BookRepoTester::TestUpdate()
{
	BookRepo BR;
	Book A = Book("asd", "asd", "action", 1234);
	BR.store(A);

	Book Updated = Book("Wcycles", "Tom Robert", "Crime", 1234);
	BR.update(A, Updated);
	Book CopyA = BR.at("Wcycles Tom Robert");
	assert(CopyA.GetAuthor() == Updated.GetAuthor());
	assert(CopyA.GetTitle() == Updated.GetTitle());
	assert(CopyA.GetGenre() == Updated.GetGenre());
	assert(CopyA.GetYear() == Updated.GetYear());

	try {
		BR.update(A, Updated);
		assert(false);
	}
	catch (const RepoError & error)
	{
		assert(error.GetMessage() == "Inexisting element!\n");
	}
}
void BookRepoTester::TestPop()
{
	BookRepo BR = BookRepo();
	Book A = Book("asd", "asd", "history", 2345);

	try {
		Book B = Book("", "", "", 0);
		B = BR.pop(A);
		assert(false);
	}
	catch (const RepoError & err)
	{
		assert(err.GetMessage() == "Inexisting element!\n");
	}

	BR.store(A);
	Book PoppedA = BR.pop(A);
	assert(PoppedA.GetAuthor() == A.GetAuthor());
	assert(PoppedA.GetTitle()  == A.GetTitle());
	assert(PoppedA.GetGenre()  == A.GetGenre());
	assert(PoppedA.GetYear()   == A.GetYear());

}
void BookRepoTester::TestIterator()
{
	BookRepo BR;
	Book a = Book("asd", "asd", "action", 1235);
	Book b = Book("add", "asd", "action", 1235);
	Book c = Book("awd", "asd", "action", 1235);

	std::vector<Book> temp;
	temp.push_back(a);
	temp.push_back(b);
	temp.push_back(c);

	BR.store(a);
	BR.store(b);
	BR.store(c);

	for (auto it = BR.begin(); it != BR.end(); it++)
		assert(it->second == temp[std::distance(BR.begin(), it)]);
}
void BookRepoTester::RunAll()
{
	TestStore();
	TestGet();
	TestIterator();
	TestUpdate();
	TestPop();
}

