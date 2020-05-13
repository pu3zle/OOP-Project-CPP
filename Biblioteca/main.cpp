#include <iostream>
#include "tests.h"
#include "ui.h"
#include "book_service.h"
#include "cart_service.h"
#include "cart_repo.h"
#include "book_repo.h"
#include "fail_repo.h"
#include "book_file_repo.h"
#include "book_validator.h"
#include "DynamicArray.h"
#include "book.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>



/*

Creati o aplicație care permite:
· gestiunea unei liste de carti. Carte: titlu, autor, gen, anul aparitiei
· adaugare, stergere, modificare și afisare carti
· cautare carte
· filtrare carti dupa: titlu, anul apariției
· sortare carti dupa titlu, autor, anul aparitiei + gen
*/


/*
1. Modificati Repository, in loc ca produsele sa se tina intr-o lista sa se tina intr-un dictionar. Interfata Repository nu trebuie sa fie modificata (ex. la get all in continuare se va returna std::vector<>)
2. Folositi in proiectul vostru fiecare din aceste functii:
	- std::copy_if (la filtrare)
	- std::transform (la raportul ce l-ati facut saptamana trecuta, inlocuind forul acela care lua din map si returna un array)
	- std:accumulate (la calcularea unui pret total sau ceva asemanator, ce se potriveste problemei ce o aveti. Daca nu aveti functionalitate de calculare total, creati o optiune noua. Daca nu aveti valori numerice, folositi functia asta in UI la concatenarea de stringuri ce trebuie afisate.)
*/

void GetDefaults(std::string& d_filename, std::string& d_extension)
{
	std::ifstream in("defaultsettings");
	if (in.peek() == EOF)
	{
		in.close();
		std::ofstream out("defaultsettings");
		out << "filename=\"default\"\nextension=\"txt\"";
		out.close();

		d_filename = "default";
		d_extension = "txt";
		return;
	}

	std::getline(in, d_filename, '\"');
	std::getline(in, d_filename);

	d_filename.pop_back();

	std::getline(in, d_extension, '\"');
	std::getline(in, d_extension);

	d_extension.pop_back();

	return;
}

int main()
{
	//Tests Scope
	{
		AllTester AT;
		AT.RunAll();
	}
	//Main Program
	{
		std::string filename = "null", extension = "null";
		GetDefaults(filename, extension);

		std::unique_ptr<IRepo> book_file_repo = std::make_unique<BookFileRepo>(filename, extension);
		
		BookValidator book_validator;
		BookService book_service(book_file_repo, book_validator);

		CartRepo cart_repo;
		CartService cart_service(cart_repo, book_validator);

		Console ui(book_service, cart_service);
		ui.Run();

	}
	
	_CrtDumpMemoryLeaks();
}