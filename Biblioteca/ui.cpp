#include "ui.h"

void Console::ChangeDefaultSettings(const std::string& filename, const std::string& extension)
{
	std::ofstream out("defaultsettings");

	out << "filename=\"" << filename << "\"\n";
	out << "extension=\"" << extension << "\"\n";

	out.close();

	this->m_BookService.Refresh("defaultsettings");
	
	return;
}

void Console::Run()
{
	//std::string defFilename = ((BookFileRepo*)(this->m_BookService.GetRepoPtr()))->GetFileName();
	std::string defPath = "None";
	std::string defFilename = "None";
	std::string defExtension = "None";
	if (m_BookService.GetRepo().IsFileRepo())
	{

		defPath = this->m_BookService.GetRepoPath();
		auto pos = defPath.find('.');
		defFilename = defPath.substr(0, pos);
		defExtension = defPath.substr(pos + 1, defPath.npos);

		std::cout << "Currently saving inside " << defPath << "\n";
	}
	

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
		else if (cmd == "chdf")
		{
			if (m_BookService.GetRepo().IsFileRepo())
			{
				std::cout << "Enter new default filename:\n";

				std::string filename;
				std::cin >> filename;

				ChangeDefaultSettings(filename, defExtension);

				defFilename = filename;
				defPath = defFilename + "." + defExtension;

				std::cout << "\nCurrently saving inside " << defPath << "\n";
			}
			else std::cout << "No path available! Currently using a memory repo!\n";

			continue;
		}
		else if (cmd == "chde")
		{
			if (m_BookService.GetRepo().IsFileRepo())
			{

				std::cout << "Enter new default extension:\n";

				std::string extension;
				std::cin >> extension;

				ChangeDefaultSettings(defFilename, extension);

				defExtension = extension;
				defPath = defFilename + "." + defExtension;

				std::cout << "\nCurrently saving inside " << defPath << "\n";
			}
			else std::cout << "No path available! Currently using a memory repo!\n";
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

void Console::PrintCart()
{
	auto items = m_CartService.GetCart().GetReference();
	auto cart = m_CartService.GetCart();
	auto quantities = cart.GetQuantities();

	if (items.size() == 0)
	{
		std::cout << "\nYour cart is empty!\n";
		return;
	}

	std::cout << "\nYour current shopping cart:\n";
	std::string key;
	int q = 0;
	for (auto& item : items)
	{
		key = item.GetTitle() + " " + item.GetAuthor();
		q = quantities.at(key);
		std::cout <<"  "<<item<<"\n\tx"<<q<<"\n\n";
	}
	std::cout << '\n';
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

	if (m_BookService.GetRepo().IsFileRepo())
		this->m_BookService.Load();
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

	if (m_BookService.GetRepo().IsFileRepo())
		this->m_BookService.Load();
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

	if (m_BookService.GetRepo().IsFileRepo())
		this->m_BookService.Load();

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

void Console::ui_report(std::istream& is)
{
	std::string line;
	std::getline(is, line);

	if (line.size() != 0)
	{
		StringRestructuring(line);
		if (line.size() != 0)
			throw UIError("Report requires no parameters!\n");
	}

	if (m_BookService.GetRepo().IsFileRepo())
		this->m_BookService.Load();
	std::vector<BookDTO> result = m_BookService.Report();
	for (auto it : result)
	{
		std::cout << it;
	}
}


void Console::ui_add_cart(std::istream& is)
{
	std::string line;
	std::getline(is, line);

	std::vector<std::string> params = read_params(2, line);

	this->m_CartService.Add(params[0], params[1], m_BookService.GetRepo());

	this->PrintCart();
}

void Console::ui_clear_cart(std::istream& is)
{
	std::string line;
	std::getline(is, line);

	if (line.size() != 0)
	{
		StringRestructuring(line);
		if (line.size() != 0)
			throw UIError("Clear Cart requires no parameters!\n");
	}
	if (m_BookService.GetRepo().IsFileRepo())
		this->m_BookService.Load();
	m_CartService.Clear();
	this->PrintCart();

}

void Console::ui_random_cart(std::istream& is)
{
	std::string line;
	std::getline(is, line);

	std::vector<std::string> params = read_params(1, line);

	try {
		std::stoi(params[0]);
	}
	catch (std::exception)
	{
		throw UIError("Invalid data type for the argument!\n");
	}
	if (m_BookService.GetRepo().IsFileRepo())
		this->m_BookService.Load();
	m_CartService.GenerateCart(std::stoi(params[0]), m_BookService.GetRepo());
	this->PrintCart();
}

void Console::ui_save_cart(std::istream& is)
{

	std::string line;
	std::getline(is, line);

	std::vector<std::string> params = read_params(2, line);

	m_CartService.Save(params[0], params[1]);
	this->PrintCart();
}

void Console::ui_save(std::istream& is)
{
	if (!m_BookService.GetRepo().IsFileRepo())
		return;

	std::string line;
	std::getline(is, line);

	if (line.size() != 0)
	{
		StringRestructuring(line);
		if (line.size() != 0)
			throw UIError("Save requires no parameters!\n");
	}

	this->m_BookService.Save();


}

void Console::ui_undo(std::istream& is)
{
	std::string line;
	std::getline(is, line);

	if (line.size() != 0)
	{
		StringRestructuring(line);
		if (line.size() != 0)
			throw UIError("Undo requires no parameters!\n");
	}

	this->m_BookService.Undo();
}

void Console::ui_clear(std::istream& is)
{
	std::string line;
	std::getline(is, line);

	if (line.size() != 0)
	{
		StringRestructuring(line);
		if (line.size() != 0)
			throw UIError("Clear requires no parameters!\n");
	}

	this->m_BookService.Clear();
}


