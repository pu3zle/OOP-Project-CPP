#pragma once
#include <assert.h>
#include "book_validator.h"
#include "utilities.h"
#include "book.h"
#include "book_repo.h"
#include "book_service.h"

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
	void TestOstream();
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

class AllTester 
{
private:
	BookValidatorTester BVT;
	BookTester BT;
	BookRepoTester BRT;
	BookServiceTester BST;
	UtilsTester UT;
public:
	AllTester() = default;
	AllTester(const AllTester&) = delete;
	~AllTester() = default;

	void RunAll()
	{
		BVT.RunAll();
		BT.RunAll();
		BRT.RunAll();
		BST.RunAll();
		UT.RunAll();
	}
};

