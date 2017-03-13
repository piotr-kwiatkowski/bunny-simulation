#pragma once
#include "Bunny.h"
#include <list>

class Colony
{
    // metoda uruchamiana raz, na poczatku programu
    // tworzy 5 poczatkowych krolikow
	bool initialization();

	// metoda odpowiadajaca za jeden cykl (rok)
	// argument we: ilosc cykli
	bool cycle(int howManyTimes);

	Colony();

};
