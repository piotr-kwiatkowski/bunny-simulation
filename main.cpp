// TODO (Magda#1#05/18/14):
//1. losowe wybieranie imion w konstruktorze Bunny ...
//2. konstruktor Colony
//3. cycle() nie ma inicjalizowac!
//4. ...

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
