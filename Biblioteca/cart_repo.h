#pragma once
#include "book.h"
#include "book_repo.h"
#include <numeric>

class CartRepo : public BookRepo
{
private:
	std::unordered_map<std::string, int> quantities;
public:
	CartRepo() noexcept : BookRepo() {}
	
	/*
		Directly add a book into the cart
	*/
	void store(const Book& to_add);

	/*
		Add a book that exists in the library to the cart
	*/
	void store(const Book& to_find, const IRepo& BR);

	/*
		Clear the shopping cart
	*/
	void clear();

	/*
		Returns how many books you have in your shopping cart
	*/
	const int qsize() const
	{
		return std::accumulate(quantities.begin(), quantities.end(), 0, [](int init, const std::pair<std::string, int>& p) {return init + p.second; });
	}

	/*
		Get a const reference to the quantities of each item in the cart
	*/
	const std::unordered_map<std::string, int>& GetQuantities() const {
		return quantities;
	}

	const bool IsFileRepo() const noexcept override
	{
		return false;
	}
};