
#include "tests.h"

void BookFileRepoTester::TestBasic()
{
	std::string fn = "Test";
	std::string ex = "csv";
	BookFileRepo BFR(fn, ex);

	assert(BFR.GetPath() == "Test.csv");

	BFR.SetFileName("test");
	BFR.SetExtension("txt");

	assert(BFR.GetPath() == "test.txt");

	auto temp = BFR;

	assert(temp.GetPath() == "test.txt");

	BookFileRepo other(BFR);

	assert(other.GetPath() == "test.txt");


}

void BookFileRepoTester::TestRefresh()
{
	std::ofstream out("test");
	out << "filename=\"test\"\n";
	out << "extension=\"txt\"\n";
	out.close();

	BookFileRepo BFR("asd", "asd");
	BFR.Refresh("test");

	assert(BFR.GetPath() == "test.txt");

	system("del test");
}

void BookFileRepoTester::TestInherited()
{
	BookFileRepo BFR("test", "txt");

	Book B("asd", "asd", "action", 23);

	BFR.store(B);

	std::ifstream in1("test.txt");
	std::string temp;
	in1 >> temp;
	assert(temp == "asd,asd,action,23");
	in1.close();

	Book A("qwe", "qwe", "adventure", 12);
	BFR.update(B, A);

	std::ifstream in2("test.txt");
	in2 >> temp;
	assert(temp == "qwe,qwe,adventure,12");
	in2.close();

	Book C("rty", "rty", "horror", 123);
	BFR.store(C);

	BFR.pop(A);

	std::ifstream in3("test.txt");
	in3 >> temp;
	assert(temp == "rty,rty,horror,123");
	in3.close();

	Book Key("rty", "rty", "null", 0);
	auto result = BFR.get(Key);

	assert(result.GetTitle() == "rty");
	assert(result.GetAuthor() == "rty");
	assert(result.GetGenre() == "horror");
	assert(result.GetYear() == 123);

	BFR.clear();
	assert(BFR.size() == 0);

	system("del test.txt");
}

void BookFileRepoTester::RunAll()
{
	TestBasic();
	TestRefresh();
	TestInherited();
}