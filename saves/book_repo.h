#pragma once
#include "general_repo.h"
#include "book.h"

class BookRepo : public GeneralRepo<Book>
{
public:
	BookRepo() noexcept : GeneralRepo<Book>(){}
};