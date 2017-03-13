// TODO (Magda#1#05/18/14):
// 1. losowe wybieranie imion w konstruktorze Bunny
// 2. konstruktor Colony
// 3. cycle() nie ma inicjalizowac!
// 4. zabezpieczenie programu przed wywaleniem w przypadku braku pliku "Imiona.csv"
// 5. optymalizacja programu, zeby wywolywal tylko jedna metode (klasy Colony?) w main'ie

#include <iostream>
#include "Bunny.h"
#include "Colony.h"

using namespace std;

int main()
{
	cout << "Commencing..." << endl;

	Bunny oBunny1;
	Bunny oBunny2;

	oBunny1.getAll();
	oBunny2.getAll();

	return 0;
}
