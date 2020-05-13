#include "cart_repo.h"

void CartRepo::store(const Book& to_add)
{
	std::string key = to_add.GetTitle() + " " + to_add.GetAuthor();
	if (m_elems.find(key) != m_elems.end())
	{
		quantities[key] += 1;
	}
	else
	{
		m_elems.insert({ key, to_add });
		quantities.insert({ key, 1 });
	}
}

void CartRepo::store(const Book& to_find, const IRepo& BR)
{
	auto book = BR.get(to_find);
	
	std::string key = book.GetTitle() + " " + book.GetAuthor();

	if (m_elems.find(key) != m_elems.end())
	{
		quantities[key] += 1;
	}
	else
	{
		m_elems.insert({ key, book });
		quantities.insert({ key, 1 });
	}
}

void CartRepo::clear()
{
	quantities.clear();
	BookRepo::clear();
}
