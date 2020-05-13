#pragma once
#include "book_service.h"

class UIError : public GeneralError {
public:
	UIError(std::string message) : GeneralError(message) {}
};

class Console {
private:
	//Fiecare nume de comanda este mapat unui pointer catre o functie membra a clasei
	typedef void(Console::*MemberFunctionPtr)(std::istream&);
	std::unordered_map<std::string,MemberFunctionPtr> commands;
	BookService& m_BookService;

	const std::string help_menu = R"(
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	add <title> <author> <genre> <year>

	del <title> <author>

	print

	cgenres

	find <title> <author>

	filter <title> OR <author>

	sort "title" OR "author" OR "genre" OR "year"  (without quotation marks)

	update <title> <author> <newtitle> <newauthor> <newgenre> <newyear>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
)";
	//Functiile au ca parametru referinta catre istream unde continui citirea de unde am ramas
	std::vector<std::string> read_params(int number, std::string&);
	void ui_get_genres(std::istream&);
	void ui_add_book(std::istream&);
	void ui_print_books(std::istream&);
	void ui_del_book(std::istream&);
	void ui_find_book(std::istream&);
	void ui_filter_books(std::istream&);
	void ui_update_book(std::istream&);
	void ui_sort_books(std::istream&);
public:
	Console(BookService& bs)
		: m_BookService(bs)
	{
		this->commands.insert({ "add",     &Console::ui_add_book     });
		this->commands.insert({ "print",   &Console::ui_print_books  });
		this->commands.insert({ "del",     &Console::ui_del_book     });
		this->commands.insert({ "find",    &Console::ui_find_book    });
		this->commands.insert({ "filter",  &Console::ui_filter_books });
		this->commands.insert({ "update",  &Console::ui_update_book  });
		this->commands.insert({ "sort",    &Console::ui_sort_books   });
		this->commands.insert({ "cgenres", &Console::ui_get_genres     });
	}
	void Run();
};