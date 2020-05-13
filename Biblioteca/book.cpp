#include "book.h"


Book::Book(const Book& other)
{
	m_title = other.m_title;
	m_author = other.m_author;
	m_genre = other.m_genre;
	m_year = other.m_year;
}

Book& Book::operator=(const Book& other)
{
	if (this == &other)
		return *this;

	m_title = other.m_title;
	m_author = other.m_author;
	m_genre = other.m_genre;
	m_year = other.m_year;
	return *this;

}

bool Book::operator==(const Book& other) const
{
	return (this->GetTitle() == other.GetTitle() && this->GetAuthor() == other.GetAuthor());
}

bool Book::operator!=(const Book& other) const
{
	return !(this->operator==(other));
}

Book::~Book()
{
}

std::ostream& operator<<(std::ostream& os, const Book& book)
{
	os << book.m_title << "," << book.m_author << "," << book.m_genre << "," << book.m_year;
	return os;
}

std::istream& operator>>(std::istream& is, Book& book)
{
	std::string tmp;
	
	std::getline(is, tmp, ',');
	book.m_title = tmp;

	std::getline(is, tmp, ',');
	book.m_author = tmp;

	std::getline(is, tmp, ',');
	book.m_genre = tmp;

	std::getline(is, tmp);
	book.m_year = std::stoi(tmp);

	return is;
}

std::ostream& operator<<(std::ostream& os, const BookDTO& b)
{
	os << "Type: " << b.type << " : " << b.count << '\n';
	os << "\tBooks:\n\t -> ";
	for (auto it : b.titles)
		os << it;
	os << '\n';
	return os;
}

void BookDTO::addTitle(const std::string& to_add)
{
	titles.push_back(to_add);
	count++;
}

const std::string& BookDTO::getType() const
{
	return this->type;
}

const int BookDTO::getCount() const
{
	return count;
}

bool BookDTO::operator==(const BookDTO& other)
{
	return this->type == other.getType();
}
