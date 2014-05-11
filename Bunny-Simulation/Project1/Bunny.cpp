#include "Bunny.h"
#include <iostream>

void Bunny::printAge()
{
	std::cout << "Wiek królika: " << Bunny::age << std::endl;
}

void Bunny::changeAge()
{
	std::cout << "Podaj wiek królika: ";
	std::cin >> Bunny::age;
}

void Bunny::printAll()
{
	std::cout << "Sex: ";
	if (Bunny::sex == male)
	{
		std::cout << "male" << std::endl;
	}
	else if (Bunny::sex == female)
	{
		std::cout << "female" << std::endl;
	}
	else
	{
		std::cout << "INVALID" << std::endl;
	}

	std::cout << "Age: " << Bunny::age << std::endl;
	std::cout << "Radioactive mutant vampire bunny: ";
	if(Bunny::rmvb = false)
	{
		std::cout << "no" << std::endl;
	}
	else if (Bunny::rmvb = true)
	{
		std::cout << "YES" << std::endl;

Bunny::Bunny(int s, int a, bool r)
{
	sex = s;
	age = a;
	rmvb = r;
}