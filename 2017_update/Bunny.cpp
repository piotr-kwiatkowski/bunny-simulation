#include <iostream>
#include "Bunny.h"

// ctor
Bunny::Bunny(std::string a_name, std::string a_sex, std::string a_color, int a_age, bool a_mutant) 
	: name(a_name), sex(a_sex), color(a_color), age(a_age), isRadioactiveVampireMutant(a_mutant)
{
	//std::cout << "bunny ctor\n";
}

std::string Bunny::getName()
{
	return this->name;
}

std::string Bunny::getSex()
{
	return this->sex;
}

std::string Bunny::getColor()
{
	return this->color;
}

int Bunny::getAge()
{
	return this->age;
}

bool Bunny::getIsRadioactiveVampireMutant()
{
	return this->isRadioactiveVampireMutant;
}
