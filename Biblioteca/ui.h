#pragma once
#include "book_service.h"
#include "cart_service.h"

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
	CartService& m_CartService;
	const std::string help_menu = R"(
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	add <title> <author> <genre> <year>

	del <title> <author>

	print

	cgenres

	find <title> <author>

	filter <title> OR <year>

	sort "title" OR "author" OR "genre" OR "year"  (without quotation marks)

	update <title> <author> <newtitle> <newauthor> <newgenre> <newyear>

	report

	add_cart <title> <author>

	clear_cart 

	random_cart <how_many>

	save_cart <filename> <extension> (extension must be in lowercase)
	
	chdf - change default filename   

	chde - change default extension

	undo	

	exit

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
)";
	//Functiile au ca parametru referinta catre istream unde continui citirea de unde am ramas
	std::vector<std::string> read_params(int number, std::string&);
	void PrintCart();
	void ChangeDefaultSettings(const std::string& filename, const std::string& extension);
	void ui_get_genres(std::istream&);
	void ui_add_book(std::istream&);
	void ui_print_books(std::istream&);
	void ui_del_book(std::istream&);
	void ui_find_book(std::istream&);
	void ui_filter_books(std::istream&);
	void ui_update_book(std::istream&);
	void ui_sort_books(std::istream&);
	void ui_report(std::istream&);
	void ui_add_cart(std::istream&);
	void ui_clear_cart(std::istream&);
	void ui_random_cart(std::istream&);
	void ui_save_cart(std::istream&);
	void ui_save(std::istream&);
	void ui_undo(std::istream&);
	void ui_clear(std::istream&);
public:
	Console(BookService& bs, CartService& cs)
		: m_BookService(bs)
		, m_CartService(cs)
	{
		this->commands.insert({ "add",			&Console::ui_add_book     });
		this->commands.insert({ "print",		&Console::ui_print_books  });
		this->commands.insert({ "del",			&Console::ui_del_book     });
		this->commands.insert({ "find",			&Console::ui_find_book    });
		this->commands.insert({ "filter",		&Console::ui_filter_books });
		this->commands.insert({ "update",		&Console::ui_update_book  });
		this->commands.insert({ "sort",			&Console::ui_sort_books   });
		this->commands.insert({ "cgenres",		&Console::ui_get_genres   });
		this->commands.insert({ "report",		&Console::ui_report       });
		this->commands.insert({ "clear",		&Console::ui_clear		  });
		this->commands.insert({ "add_cart",     &Console::ui_add_cart	  });
		this->commands.insert({ "clear_cart",   &Console::ui_clear_cart	  });
		this->commands.insert({ "random_cart",  &Console::ui_random_cart  });
		this->commands.insert({ "save_cart",    &Console::ui_save_cart	  });
		this->commands.insert({ "save",         &Console::ui_save		  });
		this->commands.insert({ "undo",         &Console::ui_undo		  });
	}
	void Run();
};