#include "book_service.h"

const BookRepo& BookService::GetRepo() const noexcept
{
	return *(dynamic_cast<BookRepo*>(this->m_BookRepo.get()));
}

void BookService::Save() const noexcept
{
	dynamic_cast<BookFileRepo*>(this->m_BookRepo.get())->SaveToFile();
}

void BookService::Load() noexcept
{
	dynamic_cast<BookFileRepo*>(this->m_BookRepo.get())->LoadFromFile();
}

void BookService::Refresh(const std::string& defaultsettings)
{
	dynamic_cast<BookFileRepo*>(this->m_BookRepo.get())->Refresh(defaultsettings);
}

void BookService::SetPath(const std::string& newFilename, const std::string& newExtension)
{
	dynamic_cast<BookFileRepo*>(this->m_BookRepo.get())->SetPath(newFilename, newExtension);
}

void BookService::Undo()
{
	if (m_undoActions.empty())
		throw ServiceError("No more undo operations left!\n");

	m_undoActions.back()->DoUndo();
	m_undoActions.pop_back();
}

std::string BookService::GetRepoPath()
{
	return dynamic_cast<BookFileRepo*>(this->m_BookRepo.get())->GetPath();
}

void BookService::Add(std::string& title, std::string& author, std::string& genre, int year)
{
	StringCapitalize(title);
	StringCapitalize(author);
	StringCapitalize(genre);
	Book temp = Book(title, author, genre, year);

	m_BookValidator.ValidateBook(temp);
	m_BookRepo->store(temp);

	m_undoActions.push_back(std::make_unique<UndoAdd>(temp, m_BookRepo.get()));
}

const Book& BookService::Find(std::string& title, std::string& author) const
{
	m_BookValidator.ValidateString(title);
	m_BookValidator.ValidateString(author);

	StringCapitalize(title);
	StringCapitalize(author);

	const Book Key = Book(title, author, "", 0);
	return m_BookRepo->get(Key);
}

void BookService::Update(std::string& TitleToFind, std::string& AuthorToFind, std::string&UpdatedTitle, std::string&UpdatedAuthor, std::string&UpdatedGenre, int UpdaterYear)
{
	StringCapitalize(TitleToFind);
	StringCapitalize(AuthorToFind);

	StringCapitalize(UpdatedAuthor);
	StringCapitalize(UpdatedTitle);
	StringCapitalize(UpdatedGenre);
	
	Book Key = Book(TitleToFind, AuthorToFind, "", 0);
	Book Update = Book(UpdatedTitle, UpdatedAuthor, UpdatedGenre, UpdaterYear);
	m_BookValidator.ValidateBook(Update);

	auto old = m_BookRepo->get(Key);

	m_BookRepo->update(Key, Update);

	m_undoActions.push_back(std::make_unique<UndoUpdate>(old, Update, m_BookRepo.get()));
}

std::vector<Book> BookService::Sort(int criteria) const
{
	std::vector<Book> copy = m_BookRepo->GetCopy();
	switch (criteria)
	{
	case 1:
		//by title
		std::sort(copy.begin(), copy.end(), Book::CompareTitle);
		break;
	case 2:
		//by author
		std::sort(copy.begin(), copy.end(), Book::CompareAuthor);
		break;
	case 3:
		//by genre
		std::sort(copy.begin(), copy.end(), Book::CompareGenre);
		break;
	case 4:
		//by year
		std::sort(copy.begin(), copy.end(), Book::CompareYear);
		break;
	default:
		break;
	}
	return copy;
}

std::vector<Book> BookService::Filter(std::string& criteria) const
{
	std::vector<Book> copy = m_BookRepo->GetCopy();
	std::vector<Book> result;

	int c;
	try {
		c = std::stoi(criteria);
	}
	catch (std::exception)
	{
		StringCapitalize(criteria);
		std::copy_if(copy.begin(), copy.end(), std::back_inserter(result), [&criteria](const Book& x) { return x.GetTitle() == criteria; });
		/*for (auto x : copy)
		{
			if (x.GetTitle() == criteria)
				result.push_back(x);
		}*/
		return result; 
	}
	std::copy_if(copy.begin(), copy.end(), std::back_inserter(result), [&c](const Book& x) { return x.GetYear() == c; });
	/*for (auto x : copy)
	{
		if (x.GetYear() == c)
			result.push_back(x);aa
	}*/
	return result;
	
}

Book BookService::Delete(std::string& title, std::string& author)
{
	StringCapitalize(title);
	StringCapitalize(author);

	m_BookValidator.ValidateString(title);
	m_BookValidator.ValidateString(author);

	Book Key = Book(title, author, "", 0);

	auto removed = m_BookRepo->pop(Key);

	m_undoActions.push_back(std::make_unique<UndoDelete>(removed, m_BookRepo.get()));

	return removed;

}

const std::list<std::string>& BookService::GetGenres() const
{
	return m_BookValidator.GetGenres();
}


std::vector<BookDTO> BookService::Report() const
{
	std::vector<Book> copy = m_BookRepo->GetCopy();

	std::unordered_map<std::string, BookDTO> report;

	for (auto it : copy)
	{
		std::unordered_map<std::string, BookDTO>::iterator position = report.find(it.GetGenre());
		if (position == report.end())
			report.insert({ it.GetGenre(), BookDTO(it.GetTitle(), it.GetGenre(), 1) });
		else {
			position->second.addTitle(it.GetTitle());
		}
	}

	std::vector<BookDTO> result;

	std::transform(report.begin(), report.end(), std::back_inserter(result), [](const std::pair<std::string, BookDTO>& p) {return p.second; });
	/*for (auto it : report)
	{
		result.push_back(it.second);
	}*/
	return result;

}

void BookService::Clear()
{
	m_undoActions.push_back(std::make_unique<UndoClear>(m_BookRepo.get(), m_BookRepo->GetReference()));
	this->m_BookRepo->clear();
}