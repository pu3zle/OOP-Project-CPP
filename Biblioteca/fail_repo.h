#pragma once

#include "book.h"
#include "book_repo.h"


class FailRepo : public BookRepo {
private:
	int m_failChance;
	
public:
	FailRepo(double failChance) noexcept
	{
		BookRepo();
		m_failChance = static_cast<int>(failChance * 1000);
	}

	void Fail() const
	{
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> m_dist(0, 1000);
		if (m_dist(mt) <= m_failChance)
			throw GeneralError("Random exception!\n");
	}

	const std::vector<Book> GetReference() const
	{
		Fail();
		return BookRepo::GetReference();
	}
	std::vector<Book> GetCopy() const {
		Fail();
		return BookRepo::GetCopy();
	}
	void clear() {
		Fail();
		BookRepo::clear();
	}
	const bool empty() const {
		Fail();
		return BookRepo::empty();
	}
	const Book& get(const Book& to_get) {
		Fail();
		return BookRepo::get(to_get);
	}
	const Book& get(const Book& to_get) const {
		Fail();
		return BookRepo::get(to_get);
	}
	Book& operator[](const std::string key) {
		Fail();
		return BookRepo::operator[](key);
	}
	const Book& at(const std::string key) const {
		Fail();
		return BookRepo::at(key);
	}
	Book pop(const Book& to_remove) {
		Fail();
		return BookRepo::pop(to_remove);
	}
	const int size() const noexcept {
		Fail();
		return BookRepo::size();
	}
	void store(const Book& to_add) {
		Fail();
		BookRepo::store(to_add);
	}
	void update(const Book& which, const Book& updated) {
		Fail();
		BookRepo::update(which, updated);
	}
};