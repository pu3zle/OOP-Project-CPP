#include "book_service.h"

const BookRepo& BookService::GetRepo() const noexcept
{
	return m_BookRepo;
}

void BookService::Add(std::string& title, std::string& author, std::string& genre, int year)
{
	StringCapitalize(title);
	StringCapitalize(author);
	StringCapitalize(genre);
	Book temp = Book(title, author, genre, year);

	m_BookValidator.ValidateBook(temp);
	m_BookRepo.store(temp);
}

const Book& BookService::Find(std::string& title, std::string& author)
{
	m_BookValidator.ValidateString(title);
	m_BookValidator.ValidateString(author);

	StringCapitalize(title);
	StringCapitalize(author);

	const Book Key = Book(title, author, "", 0);
	return m_BookRepo.get(Key);
}

void BookService::Update(std::string& TitleToFind, std::string& AuthorToFind, std::string&UpdatedTitle, std::string&UpdatedAuthor, std::string&UpdatedGenre, int UpdaterYear)
{
	StringCapitalize(TitleToFind);
	StringCapitalize(AuthorToFind);

	StringCapitalize(UpdatedAuthor);
	StringCapitalize(UpdatedTitle);
	StringCapitalize(UpdatedGenre);
	
	Book Key = Book(TitleToFind, AuthorToFind, "", 0);
	Book Update = Book(UpdatedTitle, UpdatedAuthor, UpdatedGenre, UpdaterYear);
	m_BookValidator.ValidateBook(Update);

	m_BookRepo.update(Key, Update);


}

std::vector<Book> BookService::Sort(int criteria)
{
	std::vector<Book> copy = m_BookRepo.GetCopy();
	switch (criteria)
	{
	case 1:
		//by title
		sort(copy.begin(), copy.end(), [](const Book& a, const Book& b) {return a.GetTitle() < b.GetTitle(); });
		break;
	case 2:
		//by author
		sort(copy.begin(), copy.end(), [](const Book& a, const Book& b) {return a.GetAuthor() < b.GetAuthor(); });
		break;
	case 3:
		//by genre
		sort(copy.begin(), copy.end(), [](const Book& a, const Book& b) {return a.GetGenre() < b.GetGenre(); });
		break;
	case 4:
		//by year
		sort(copy.begin(), copy.end(), [](const Book& a, const Book& b) {return a.GetYear() < b.GetYear(); });
		break;
	default:
		break;
	}
	return copy;
}

std::vector<Book> BookService::Filter(std::string& criteria)
{
	std::vector<Book> copy = m_BookRepo.GetCopy();
	std::vector<Book> result;

	int c;
	try {
		c = std::stoi(criteria);
	}
	catch (std::exception)
	{
		StringCapitalize(criteria);
		for (auto x : copy)
		{
			if (x.GetTitle() == criteria)
				result.push_back(x);
		}
		return result; 
	}
	for (auto x : copy)
	{
		if (x.GetYear() == c)
			result.push_back(x);
	}
	return result;
	
}

Book BookService::Delete(std::string& title, std::string& author)
{
	StringCapitalize(title);
	StringCapitalize(author);

	m_BookValidator.ValidateString(title);
	m_BookValidator.ValidateString(author);

	Book Key = Book(title, author, "", 0);

	return m_BookRepo.pop(Key);

}

const std::list<std::string>& BookService::GetGenres()
{
	return m_BookValidator.GetGenres();
}