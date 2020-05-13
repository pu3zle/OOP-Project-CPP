#pragma once
#include "book_repo.h"
#include <fstream>

class BookFileRepo : public BookRepo
{
private:
	std::string m_filename;
	std::string m_extension;
public:
	BookFileRepo() noexcept : BookRepo() {}
	BookFileRepo(const std::string& filename, const std::string& extension)
	{
		BookRepo();
		this->m_filename = filename;
		this->m_extension = extension;
	}
	BookFileRepo(const BookFileRepo& other) noexcept
	{
		auto safe_copy = other.m_elems;
		this->m_elems = safe_copy;
		this->m_filename = other.m_filename;
		this->m_extension = other.m_extension;
	}
	BookFileRepo& operator=(const BookFileRepo& other) noexcept
	{
		auto safe_copy = other.m_elems;
		this->m_elems = safe_copy;
		this->m_filename = other.m_filename;
		this->m_extension = other.m_extension;
	}

	const bool IsFileRepo() const noexcept override
	{
		return true;
	}
	void SetFileName(const std::string& oFileName) noexcept
	{
		this->m_filename = oFileName;
	}

	void SetExtension(const std::string& oExtension) noexcept
	{
		this->m_extension = oExtension;
	}

	void SetPath(const std::string& oFileName, const std::string& oExtension) noexcept
	{
		this->m_filename = oFileName;
		this->m_extension = oExtension;
	}

	const std::string GetPath() const noexcept
	{
		std::string path = this->m_filename + "." + this->m_extension;
		return path;
	}

	void Refresh(const std::string& defaultsettings) noexcept
	{
		std::ifstream in(defaultsettings);

		std::getline(in, m_filename, '\"');
		std::getline(in, m_filename);

		m_filename.pop_back();

		std::getline(in, m_extension, '\"');
		std::getline(in, m_extension);

		m_extension.pop_back();

		return;
	}

	void SaveToFile()
	{
		std::string path = this->m_filename + "." + this->m_extension;
		std::ofstream out(path);
		/*for (auto& it = m_elems.begin(); it != m_elems.end(); it++)
		{
			out << *it << "\n";
		}*/
		for (const auto& el : m_elems)
		{
			out << el.second << '\n';
		}
		out.close();
	}

	void LoadFromFile()
	{
		std::string path = this->m_filename + "." + this->m_extension;
		std::ifstream in(path);
		while (in.peek() != EOF)
		{
			Book e;
			in >> e;
			std::string key = e.GetTitle() + " " + e.GetAuthor();
			m_elems.insert({key, e});
		}
		in.close();
	}

	void store(const Book& to_add) override
	{
		this->LoadFromFile();
		BookRepo::store(to_add);
		this->SaveToFile();
	}

	const Book& get(const Book& to_get) override
	{
		this->LoadFromFile();
		return BookRepo::get(to_get);
	}

	void update(const Book& which, const Book& updated) override
	{
		this->LoadFromFile();
		BookRepo::update(which, updated);
		this->SaveToFile();
	}

	Book pop(const Book& to_remove) override
	{
		this->LoadFromFile();
		auto result = BookRepo::pop(to_remove);
		this->SaveToFile();
		return result;
	}

	void clear() override
	{
		this->LoadFromFile();
		BookRepo::clear();
		this->SaveToFile();
	}
	
};