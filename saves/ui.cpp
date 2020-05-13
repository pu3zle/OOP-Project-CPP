#include "ui.h"

void Console::Run()
{
	std::string cmd;
	while (true)
	{
		std::cout << ">> ";
		std::cin >> cmd;
		if (cmd == "exit")
		{
			std::cout << "Process Terminated!\n";
			return;
		}
		else if (cmd == "help")
		{
			std::cout << help_menu;
			continue;
		}
		auto it = commands.find(cmd);
		if (it != commands.end())
		{
			auto function = (*it).second;
			try {
				(this->*function)(std::cin);
				std::cout << "\nDone!\n";
			}
			catch (const GeneralError & err) {
				std::cout << err.GetMessage();
			}
		}
		else {
			std::cout << "Invalid command!\n";
		}
	}

}

std::vector<std::string> Console::read_params(int number, std::string& line)
{
	if (line.size() == 0)
	{
		throw UIError("Invalid number of parameters!\n");
	}
	//Gets rid of unnecessary spaces
	StringRestructuring(line);
	if (line.size() == 0)
	{
		throw UIError("Invalid number of parameters!\n");
	}

	std::vector<std::string> params;

	unsigned int start = 0;
	for (int i = 0; i < number; i++)
	{
		try {
			std::string result = GetWord(line, start);
			params.push_back(result);
		}
		catch (const GeneralError&)
		{
			throw UIError("Invalid number of parameters!\n");
		}
	}

	if (start < line.size())
		throw UIError("Invalid number of parameters!\n");

	return params;
}

void Console::ui_get_genres(std::istream& is)
{
	std::string line;
	std::getline(is, line);

	if (line.size() != 0)
	{
		StringRestructuring(line);
		if (line.size() != 0)
			throw UIError("Print requires no parameters!\n");
	}

	std::cout << "The valid genres are: \n";
	for (const auto& it : m_BookService.GetGenres())
	{
		std::cout << it << " ";
	}
	std::cout << '\n';
}

void Console::ui_add_book(std::istream& is)
{
	std::string line;
	std::getline(is, line);

	std::vector<std::string> params = this->read_params(4, line);
	
	try {
		std::stoi(params[3]);
	}
	catch (std::exception)
	{
		throw UIError("Invalid data type for the last argument!\n");
	}

	m_BookService.Add(params[0], params[1], params[2], std::stoi(params[3]));

	
}

void Console::ui_print_books(std::istream& is)
{
	std::string line;
	std::getline(is, line);

	if (line.size() != 0)
	{
		StringRestructuring(line);
		if (line.size() != 0)
			throw UIError("Print requires no parameters!\n");
	}

	const auto& list = m_BookService.GetRepo().GetReference();

	if(list.empty())
	{
		std::cout << "The list is empty!\n";
		return;
	}
	for (const auto& element : list)
	{
		std::cout << element<<'\n';
	}
}

void Console::ui_del_book(std::istream& is)
{
	std::string line;
	std::getline(is, line);
	
	std::vector<std::string> params = read_params(2,line);

	m_BookService.Delete(params[0], params[1]);

}

void Console::ui_find_book(std::istream& is)
{
	std::string line;
	std::getline(is, line);

	std::vector<std::string> params = read_params(2, line);

	try {
		auto result = m_BookService.Find(params[0], params[1]);
		std::cout << "The book is in stock!\n";
	}
	catch (const GeneralError&)
	{
		std::cout << "The book is not in stock!\n";
	}
}

void Console::ui_filter_books(std::istream& is)
{
	std::string line;
	std::getline(is, line);

	std::vector<std::string> params = read_params(1, line);

	std::vector<Book> result;

	result = m_BookService.Filter(params[0]);

	if (result.empty())
	{
		std::cout << "No results found!\n";
		return;
	}

	for (auto it : result)
	{
		std::cout << it << '\n';
	}

}

void Console::ui_update_book(std::istream& is)
{
	std::string line;
	std::getline(is, line);

	std::vector<std::string> params = read_params(6,line);

	try {
		std::stoi(params[5]);
	}
	catch (std::exception)
	{
		throw UIError("Invalid data type for the last argument!\n");
	}

	m_BookService.Update(params[0], params[1], params[2], params[3], params[4], std::stoi(params[5]));
}

void Console::ui_sort_books(std::istream& is)
{
	std::string line;
	std::getline(is, line);

	std::vector<std::string> params = read_params(1, line);

	std::vector<Book> result;

	if (params[0] == "title")
		result = m_BookService.Sort(1);
	else if (params[0] == "author")
		result = m_BookService.Sort(2);
	else if (params[0] == "genre")
		result = m_BookService.Sort(3);
	else if (params[0] == "year")
		result = m_BookService.Sort(4);
	else {
		throw UIError("Invalid option!\n");
	}

	if (result.empty())
	{
		std::cout << "The list is empty!\n";
		return;
	}

	for (auto it : result)
	{
		std::cout << it << '\n';
	}
}


