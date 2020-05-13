#pragma once
#include "utilities.h"


class Book {
private:
	std::string m_title;
	std::string m_author;
	std::string m_genre;
	int m_year;
public:
	Book(const std::string& title, const std::string& author, const std::string& genre, int year) : m_title(title),m_author(author),m_genre(genre),m_year(year) {}
	Book(const Book& other);
	Book& operator=(const Book& other);
	
	std::string GetTitle()const{
		return m_title; 
	}
	std::string GetAuthor()const{
		return m_author; 
	}
	std::string GetGenre() const{
		return m_genre; 
	}
	int GetYear() const noexcept{
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
	friend std::ostream& operator<<(std::ostream& os, const Book& book);

	~Book();
};

