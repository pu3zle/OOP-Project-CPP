#include "cart_service.h"

const CartRepo& CartService::GetCart() const noexcept
{
	return m_Cart;
}

void CartService::Add(std::string& title, std::string& author, const IRepo& BR)
{
	m_BookValidator.ValidateString(title);
	m_BookValidator.ValidateString(author);

	StringCapitalize(title);
	StringCapitalize(author);

	Book to_find = Book(title, author, "", 0);

	m_Cart.store(to_find, BR);

}

void CartService::Clear()
{
	m_Cart.clear();
}

void CartService::GenerateCart(int n, const IRepo& BR)
{
	if (BR.empty())
		throw RepoError("The library is empty! Add books first!\n");

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(0, BR.size()-1);

	auto copy = BR.GetReference();

	int randint = 0;
	for (int i = 0; i < n; i++)
	{
		randint = dist(mt);
		m_Cart.store(copy.at(randint));
	}
}

void CartService::Save(std::string& filename, std::string& extension) const
{
	if (m_Cart.empty())
		throw GeneralError("The cart is empty!\n");

	if (extension != "csv" && extension != "html")
		throw GeneralError("Invalid extension!\n");

	std::string to_open = filename + "." + extension;
	std::ofstream out(to_open);

	std::string key;

	if(extension == "csv")
	for (auto& item : m_Cart.GetReference())
	{
		key = item.GetTitle() + " " + item.GetAuthor();
		for(int i = 0; i < m_Cart.GetQuantities().at(key); i++)
			out << item.GetTitle() << "," << item.GetAuthor() << "," << item.GetGenre() << "," << item.GetYear()<<'\n';
	}

	else
	for (auto& item : m_Cart.GetReference())
	{
		key = item.GetTitle() + " " + item.GetAuthor();
		for (int i = 0; i < m_Cart.GetQuantities().at(key); i++)
			out << item.GetTitle() << "	" << item.GetAuthor() << " " << item.GetGenre() << " " << item.GetYear() << "<br>";
	}
	out << '\n';
	out.close();
}
