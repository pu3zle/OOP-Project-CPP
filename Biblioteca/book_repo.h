#pragma once
#include <vector>
#include <unordered_map>
#include "utilities.h"
#include "book.h"

class RepoError : public GeneralError {
public:
	RepoError(std::string message) : GeneralError(message){}
};

class IRepo {
public:
	virtual const bool IsFileRepo() const noexcept = 0;
	virtual const std::vector<Book> GetReference() const = 0;
	virtual std::vector<Book> GetCopy() const = 0;
	virtual void clear() = 0;
	virtual const bool empty() const = 0;
	virtual const Book& get(const Book& to_get) = 0;
	virtual const Book& get(const Book& to_get) const = 0;
	virtual Book& operator[](const std::string key) = 0;
	virtual const Book& at(const std::string key) const = 0;
	virtual Book pop(const Book& to_remove) = 0;
	virtual const int size() const noexcept = 0;
	virtual void store(const Book& to_add) = 0;
	virtual void update(const Book& which, const Book& updated) = 0;
	virtual ~IRepo() = default;
};


class BookRepo : public IRepo {
protected:
	std::unordered_map<std::string, Book> m_elems;
public:
	BookRepo() noexcept {}
	BookRepo(const BookRepo& other)
	{
		this->m_elems = other.m_elems;
	}

	virtual const bool IsFileRepo() const noexcept 
	{
		return false;
	}

	std::unordered_map<std::string, Book>::iterator begin() noexcept
	{
		return m_elems.begin();
	}
	std::unordered_map<std::string, Book>::iterator end() noexcept
	{
		return m_elems.end();
	}

	//get a const copy to the container
	virtual const std::vector<Book> GetReference() const
	{
		std::vector<Book> elems;
		elems.reserve(m_elems.size());

		for (const auto& it : m_elems)
		{
			elems.push_back(it.second);
		}

		//std::transform(m_elems.begin(), m_elems.end(), elems.begin(), [](typename std::unordered_map<std::string, Book>::iterator p) {return p.second; });
		
		return elems;
	}
	//get a copy of the container
	virtual std::vector<Book> GetCopy() const {
		std::vector<Book> elems;
		elems.reserve(m_elems.size());


		for (const auto& it : m_elems)
		{
			elems.push_back(it.second);
		}

		//std::transform(m_elems.begin(), m_elems.end(), elems.begin(), [](auto pair) {return pair.second; });

		return elems;
	}

	virtual Book& at(const std::string key)
	{
		return m_elems.at(key);
	}
	virtual Book& operator[](const std::string key)
	{
		return m_elems.at(key);
	}

	virtual const Book& at(const std::string key) const
	{
		return m_elems.at(key);
	}

	virtual const int size() const noexcept
	{
		return m_elems.size();
	}
	virtual const bool empty() const
	{
		return m_elems.empty();
	}

	//Create
	virtual void store(const Book& to_add)
	{
		std::string key = to_add.GetTitle() + " " + to_add.GetAuthor();
		auto pos = m_elems.find(key);
		//std::find_if(m_elems.begin(), m_elems.end(), [&to_add](std::pair<std::string, Book> existing) { return existing.second == to_add; });
		
		if (pos != m_elems.end())
			throw RepoError("Already existing element!\n");

		m_elems.insert({ key  ,to_add });
	}
	//Read
	virtual const Book& get(const Book& to_get) const
	{
		//std::find_if(m_elems.begin(), m_elems.end(), [&to_get](std::pair<std::string, Book> existing) { return existing.second == to_get; });
		std::string key = to_get.GetTitle() + " " + to_get.GetAuthor();
		auto pos = m_elems.find(key);

		if (pos == m_elems.end())
			throw RepoError("Inexisting element!\n");
		return pos->second;
	}
	//The FileRepo gets this one
	virtual const Book& get(const Book& to_get)
	{
		//std::find_if(m_elems.begin(), m_elems.end(), [&to_get](std::pair<std::string, Book> existing) { return existing.second == to_get; });
		std::string key = to_get.GetTitle() + " " + to_get.GetAuthor();
		auto pos = m_elems.find(key);

		if (pos == m_elems.end())
			throw RepoError("Inexisting element!\n");
		return pos->second;
	}
	//Update
	virtual void update(const Book& which, const Book& updated)
	{
		std::string key = which.GetTitle() + " " + which.GetAuthor();
		auto pos = m_elems.find(key);
		//std::find_if(m_elems.begin(), m_elems.end(), [&which](std::pair<std::string, Book> existing) { return existing.second == which; });

		if (pos == m_elems.end())
			throw RepoError("Inexisting element!\n");
		this->m_elems.erase(pos);
		key = updated.GetTitle() + " " + updated.GetAuthor();
		this->m_elems.insert({ key, updated });
	}
	//Delete
	virtual Book pop(const Book& to_remove)
	{
		std::string key = to_remove.GetTitle() + " " + to_remove.GetAuthor();
		auto pos = m_elems.find(key);
		//std::find_if(m_elems.begin(), m_elems.end(), [&to_remove](std::pair<std::string, Book> existing) { return existing.second == to_remove; });

		if (pos == m_elems.end())
			throw RepoError("Inexisting element!\n");
		Book elem = pos->second;
		this->m_elems.erase(pos);
		return elem;
	}

	virtual void clear()
	{
		this->m_elems.clear();
	}

	virtual ~BookRepo() = default;
};