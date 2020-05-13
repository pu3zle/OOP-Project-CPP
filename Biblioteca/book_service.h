#pragma once
#include "book_repo.h"
#include "book_file_repo.h"
#include "book_validator.h"
#include "utilities.h"
#include "book.h"
#include <iterator>
#include "undo.h"

class ServiceError : public GeneralError {
public:
	ServiceError(std::string message) : GeneralError(message) {}
};

class BookService {
private:
	std::unique_ptr<IRepo>& m_BookRepo;
	BookValidator& m_BookValidator;
	std::vector<std::unique_ptr<UndoAction>> m_undoActions;
public:
	BookService(std::unique_ptr<IRepo>& bookrepo, BookValidator& bookvalidator)
		: m_BookRepo(bookrepo), m_BookValidator(bookvalidator) {}
	BookService(const BookService& SB) = delete;
	~BookService() = default;

	const BookRepo& GetRepo() const noexcept;

	void Save() const noexcept;

	void Load() noexcept;

	void Refresh(const std::string& defaultsettings);

	void SetPath(const std::string& newFilename, const std::string& newExtension);

	void Undo();

	std::string GetRepoPath();

	/*
		ADD FUNCTIONALITY
		Params: string -> title, author, genre
				ints   -> year
		Details: Adds a book to the books repository
		Throws: ValidatorError, RepoError
	*/
	void Add(std::string& title, std::string& author, std::string& genre, int year);
	/*
		FIND FUNCTIONALITY
		Params: string -> title, author
		Returns: a constant copy of the book (if found)
		Throws: ValidatorError, RepoError
	*/
	const Book& Find(std::string& title, std::string& author) const;
	/*
		UPDATE FUNCTIONALITY
		Params: strings -> title, author, newtitle, newauthor, newgenre
				ints -> newyear
		Details: Updates the Book with the "title" and "author" to "newtitle", "newauthor", "newgenre" and "newyear"
		Throws: ValidatorError, RepoError
	*/
	void Update(std::string& title_to_find, std::string& author_to_find, std::string&updated_title, std::string& updated_author, std::string&updated_genre, int updated_year);
	/*
		DELETE FUNCTIONALITY
		Params: string -> title, author
		Returns: a copy of the deleted book (if found)
		Throws: ValidatorError, RepoError
	*/
	Book Delete(std::string& title, std::string& author);
	/*
		SORT FUNCTIONALITY
		Params: integer - criteria
		Returns: a vector of the sorted elements, sorted by the given criteria (1-title, 2-author, 3-genre, 4-year)
	*/
	std::vector<Book> Sort(int criteria) const;
	/*
		FILTER FUNCTIONALITY
		Params: string -> criteria
		Returns: a vector of filtered elements, given the criteria
		The function filters by what can the criteria be interpreted as (int - year, string - title)
	*/
	std::vector<Book> Filter(std::string& criteria) const;
	/*
		Returns a constant reference to the valid genres
	*/
	const std::list<std::string>& GetGenres() const;

	std::vector<BookDTO> Report() const;

	void Clear();
	
};