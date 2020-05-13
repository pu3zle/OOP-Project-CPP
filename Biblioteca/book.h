#pragma once
#include "utilities.h"


class Book {
private:
	std::string m_title;
	std::string m_author;
	std::string m_genre;
	int m_year;
public:
	Book()
		: m_title("null")
		, m_author("null")
		, m_genre("null")
		, m_year(0)
	{}
	Book(const std::string& title, const std::string& author, const std::string& genre, int year) : m_title(title),m_author(author),m_genre(genre),m_year(year) {}
	Book(const Book& other);
	Book& operator=(const Book& other);
	
	const std::string& GetTitle()const{
		return m_title; 
	}
	const std::string& GetAuthor()const{
		return m_author; 
	}
	const std::string& GetGenre() const{
		return m_genre; 
	}
	const int GetYear() const noexcept{
		return m_year; 
	}

	void SetTitle(std::string title){
		this->m_title = title; 
	}
	void SetAuthor(std::string author){
		this->m_author = author;
	}
	void SetGenre(std::string genre){
		this->m_genre = genre;
	}
	void SetYear(int year){
		this->m_year = year;
	}

	bool operator==(const Book& other) const;
	bool operator!=(const Book& other) const;


	static void swap(Book& a, Book& b)
	{
		std::swap(a.m_author, b.m_author);
		std::swap(a.m_title, b.m_title);
		std::swap(a.m_genre, b.m_genre);
		std::swap(a.m_year, b.m_year);
	}

	static bool CompareTitle(const Book& a, const Book& b)
	{
		return a.GetTitle() < b.GetTitle();
	}

	static bool CompareGenre(const Book& a, const Book& b)
	{
		return a.GetGenre() < b.GetGenre();
	}

	static bool CompareAuthor(const Book& a, const Book& b)
	{
		return a.GetAuthor() < b.GetAuthor();
	}

	static bool CompareYear(const Book& a, const Book& b)
	{
		return a.GetYear() < b.GetYear();
	}

	friend std::ostream& operator<<(std::ostream& os, const Book& book);
	friend std::istream& operator>>(std::istream& is, Book& book);

	~Book();
};

class BookDTO {
	std::vector<std::string> titles;
	std::string type;
	int count;

public:
	BookDTO(const std::string& title, const std::string& type, int count)
		: type(type), count(count)
	{
		titles.push_back(title);
	}
	void addTitle(const std::string& to_add);
	const std::string& getType() const;
	const int getCount()const;
	bool operator==(const BookDTO& other);
	friend std::ostream& operator<<(std::ostream& os, const BookDTO& b);
};