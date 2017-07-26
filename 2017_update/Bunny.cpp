#include <iostream>
#include "Bunny.h"

// Bunny class constructor
Bunny::Bunny(std::string a_name, std::string a_sex, std::string a_color, int a_age, bool a_mutant) 
	: m_name(a_name)
	, m_sex(a_sex)
	, m_color(a_color)
	, m_age(a_age)
	, m_isRadioactiveVampireMutant(a_mutant)
{}

std::string Bunny::getName()
{
	return this->m_name;
}

std::string Bunny::getSex()
{
	return this->m_sex;
}

std::string Bunny::getColor()
{
	return this->m_color;
}

int Bunny::getAge()
{
	return this->m_age;
}

bool Bunny::getIsRadioactiveVampireMutant()
{
	return this->m_isRadioactiveVampireMutant;
}

void Bunny::incrementAge()
{
    this->m_age++;
}
