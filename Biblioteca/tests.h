#pragma once
#include <assert.h>
#include "book_validator.h"
#include "utilities.h"
#include "book.h"
#include "book_repo.h"
#include "book_service.h"
#include "cart_repo.h"
#include "cart_service.h"

class BookValidatorTester 
{
private:
	BookValidator DummyValidator;
	void TestValidateYear();
	void TestValidateGenre();
	void TestValidateString();
	void TestValidateBook();
public:
	BookValidatorTester() = default;
	BookValidatorTester(const BookValidatorTester&) = delete;
	~BookValidatorTester() = default;
	void RunAll();
};

class BookTester 
{
private:
	void TestGetters();
	void TestSetters();
	void TestCopy();
	void TestEqualTo();
	void TestStream();
	void TestBookDTO();
public:
	BookTester() = default;
	BookTester(const BookTester&) = delete;
	~BookTester() = default;

	void RunAll();

};

class BookRepoTester {
private:
	void TestStore();
	void TestGet();
	void TestUpdate();
	void TestPop();
	void TestIterator();
public:
	BookRepoTester() = default;
	BookRepoTester(const BookRepoTester&) = delete;
	~BookRepoTester() = default;

	void RunAll();
};

class BookServiceTester {
private:
	void TestAdd();
	void TestGet();
	void TestUpdate();
	void TestDelete();
	void TestSort();
	void TestFilter();
	void TestGetGenres();
	void TestReport();
	void TestSaveLoadRefresh();
	void TestUndo();
public:
	BookServiceTester() = default;
	BookServiceTester(const BookServiceTester&) = delete;
	~BookServiceTester() = default;
	
	void RunAll();

};

class UtilsTester {
private:
	void TestStringRestructuring();
	void TestGetWord();
	
public:
	UtilsTester() = default;
	UtilsTester(const BookServiceTester&) = delete;
	~UtilsTester() = default;

	void RunAll();

};

class CartTester {
private:
	void TestAdd();
	void TestRandom();
	void TestClear();
	void TestSave();
public:
	void RunAll();
};

class BookFileRepoTester
{
private:
	void TestBasic();
	void TestRefresh();
	void TestInherited();
public:
	void RunAll();
};

class AllTester 
{
private:
	BookValidatorTester BVT;
	BookTester BT;
	BookRepoTester BRT;
	BookFileRepoTester BFRT;
	BookServiceTester BST;
	UtilsTester UT;
	CartTester CT;
public:
	AllTester() = default;
	AllTester(const AllTester&) = delete;
	~AllTester() = default;

	void RunAll()
	{
		BVT.RunAll();
		BT.RunAll();
		BRT.RunAll();
		BFRT.RunAll();
		BST.RunAll();
		UT.RunAll();
		CT.RunAll();
	}
};

