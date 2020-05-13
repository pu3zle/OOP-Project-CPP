#pragma once
#include "book.h"
#include "book_repo.h"

class UndoAction {
public:
	virtual void DoUndo() = 0;
	virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction {
	Book m_addedBook;
	IRepo* m_repo;

public:
	UndoAdd(const Book& book, IRepo* repo)
		: m_addedBook(book)
		, m_repo(repo)
	{}

	void DoUndo() override
	{
		m_repo->pop(m_addedBook);
	}
};

class UndoDelete : public UndoAction {
	Book m_removedBook;
	IRepo* m_repo;

public:
	UndoDelete(const Book& book, IRepo* repo)
		: m_removedBook(book)
		, m_repo(repo)
	{}

	void DoUndo() override
	{
		m_repo->store(m_removedBook);
	}
};

class UndoUpdate : public UndoAction {
	Book m_oldVersion;
	Book m_newVersion;
	IRepo* m_repo;

public:
	UndoUpdate(const Book& oldBook, const Book& newBook, IRepo* repo)
		: m_oldVersion(oldBook)
		, m_newVersion(newBook)
		, m_repo(repo)
	{}

	void DoUndo() override
	{
		m_repo->update(m_newVersion, m_oldVersion);
	}
};

class UndoClear : public UndoAction {
	IRepo* m_repo;
	std::vector<Book> m_books;
public:
	UndoClear(IRepo* repo, const std::vector<Book> books)
		: m_repo(repo)
		, m_books(books)
	{}

	void DoUndo() override
	{
		for (const auto it : m_books)
		{
			m_repo->store(it);
		}
	}

};