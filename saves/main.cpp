#include <iostream>
#include "tests.h"
#include "ui.h"
#include "book_service.h"
#include "book_repo.h"
#include "book_validator.h"
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
int main()
{
	//Tests Scope
	{
		AllTester AT;
		AT.RunAll();
	}
	//Main Program
	{
		BookRepo book_repo;
		BookValidator book_validator;
		BookService book_service(book_repo, book_validator);
		Console ui(book_service);
		ui.Run();
	}
	
	_CrtDumpMemoryLeaks();
}