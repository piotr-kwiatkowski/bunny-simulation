#include "Bunny.h"
#include <iostream>

void Bunny::printName(Bunny *oBunny)
{
	std::cout << "Wiek krolika: " << oBunny.age() << std::endl;
}