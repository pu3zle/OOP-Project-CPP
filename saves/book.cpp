#include "book.h"

void may_throw();

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

Book::~Book()
{
}

std::ostream& operator<<(std::ostream& os, const Book& book)
{
	os << book.m_title << " written by " << book.m_author << " | " << book.m_genre << ", " << book.m_year;
	return os;
}