#pragma once

#include "cart_repo.h"
#include "book_validator.h"
#include "utilities.h"
#include "book.h"
#include "book_repo.h"

class CartService {
private:
	CartRepo& m_Cart;
	BookValidator& m_BookValidator;


public:
	CartService(CartRepo& cart, BookValidator& bookvalidator)
		: m_Cart(cart)
		, m_BookValidator(bookvalidator)
	{}

	CartService(const CartService& CS) = delete;
	~CartService() = default;

	const CartRepo& GetCart() const noexcept;

	/*
		ADD FUNCTIONALITY
		Params: title - the title of the book to be added in the cart
				BR - the repository of available books
	*/
	void Add(std::string& title, std::string& author, const IRepo& BR);

	/*
		Empty the cart
	*/
	void Clear();

	/*
		Randomly generate a cart of n books
	*/
	void GenerateCart(int n, const IRepo& BR);

	/*
		Save the cart's contents in a file of HTML or CSV
	*/
	void Save(std::string& filename, std::string& extension) const;
	
};