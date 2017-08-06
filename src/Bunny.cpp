#include <iostream>
#include "Bunny.h"

// Bunny class constructor
Bunny::Bunny(std::string a_name, std::string a_sex, std::string a_color, int8_t a_age, bool a_mutant)
    : m_name(a_name)
    , m_sex(a_sex)
    , m_color(a_color)
    , m_age(a_age)
    , m_isRadioactiveVampireMutant(a_mutant)
{}

std::string Bunny::getName() const
{
    return this->m_name;
}

std::string Bunny::getSex() const
{
    return this->m_sex;
}

std::string Bunny::getColor() const
{
    return this->m_color;
}

int8_t Bunny::getAge() const
{
    return this->m_age;
}

bool Bunny::getIsMutant() const
{
    return this->m_isRadioactiveVampireMutant;
}

void Bunny::convertToMutant()
{
    this->m_isRadioactiveVampireMutant = true;
}

void Bunny::incrementAge()
{
    this->m_age++;
}

bool Bunny::operator==(const Bunny & other) const
{
    return this->getName() == other.getName() ? true : false;
}
