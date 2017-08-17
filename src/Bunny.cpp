#include <iostream>
#include <iomanip>   // std::setw
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

std::ostream& operator<<(std::ostream& os, const Bunny& a)
{
    return os << std::setw(20)
        << a.getName() << "\t"
        << a.getSex() << "\t"
        << static_cast<int>(a.getAge()) << "\t" // cast to avoid printing int8_t as char
        << a.getColor() << "\t"
        << std::boolalpha << a.getIsMutant()
        << std::noboolalpha;
}
