#pragma once
#include <vector>
#include "utilities.h"

class RepoError : public GeneralError {
public:
	RepoError(std::string message) : GeneralError(message){}
};


template <typename Element>
class GeneralRepo {
private:
	std::vector<Element> m_elems;
public:
	GeneralRepo() noexcept{}
	GeneralRepo(const GeneralRepo& other)
	{
		this->m_elems = other.m_elems;
	}
	
	static typename std::vector<Element>::iterator iterator() noexcept
	{
		typename std::vector<Element>::iterator it;
		return it;
	}

	typename std::vector<Element>::iterator begin() noexcept
	{
		return m_elems.begin();
	}
	typename std::vector<Element>::iterator end() noexcept
	{
		return m_elems.end();
	}

	//get a const reference to the container
	const std::vector<Element>& GetReference() const noexcept
	{
		return m_elems;
	}
	//get a copy of the container
	std::vector<Element> GetCopy() const {
		return m_elems;
	}

	Element& at(int pos)
	{
		return m_elems.at(pos);
	}
	Element& operator[](int pos)
	{
		return m_elems.at(pos);
	}

	const Element& at(int pos) const
	{
		return m_elems.at(pos);
	}
	const Element& operator[](int pos) const
	{
		return m_elems.at(pos);
	}

	const int size() const noexcept
	{
		return m_elems.size();
	}
	const bool empty() const
	{
		return m_elems.empty();
	}

	//Create
	void store(const Element& to_add)
	{
		auto pos = std::find_if(m_elems.begin(), m_elems.end(), [&to_add](const Element& added) {return added == to_add; });
		if (pos != m_elems.end())
			throw RepoError("Already existing element!\n");
		m_elems.push_back(to_add);
	}
	//Read
	const Element& get(const Element& to_get)
	{
		auto pos = std::find_if(m_elems.begin(), m_elems.end(), [&to_get](const Element& existing) {return existing == to_get; });
		if (pos == m_elems.end())
			throw RepoError("Inexisting element!\n");
		return *pos;
	}
	//Update
	void update(const Element& which, const Element& updated)
	{
		auto pos = std::find_if(m_elems.begin(), m_elems.end(), [&which](const Element& existing) {return existing == which; });
		if (pos == m_elems.end())
			throw RepoError("Inexisting element!\n");
		this->m_elems.at(pos - m_elems.begin()) = updated;
	}
	//Delete
	Element pop(const Element& to_remove)
	{
		auto pos = std::find_if(m_elems.begin(), m_elems.end(), [&to_remove](const Element& existing) {return existing == to_remove; });
		if (pos == m_elems.end())
			throw RepoError("Inexisting element!\n");
		Element elem = *pos;
		this->m_elems.erase(pos);
		return elem;
	}

	~GeneralRepo() = default;
};