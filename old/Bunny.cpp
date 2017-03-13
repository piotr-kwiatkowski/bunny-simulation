#include "Bunny.h"
#include <iostream>
#include <list> // list
#include <iomanip> // setw
#include <fstream> // fstream
#include <cstdlib> // rand

std::string Bunny::getName()
{
    return name;
}

std::string Bunny::setSex()
{
    int temp = rand() % 100;
    if(temp == 0 || temp == 99)
        return "vamp.";
    else if (temp > 0 && temp < 50)
        return "male";
    else if (temp >49 && temp < 99)
        return "female";
    else
    {
        std::cout << "INVALID SEX" << ".\n>>> File: " << __FILE__ << "\n>>> Line: " << __LINE__ << std::endl;
        return "INVALID";
    }
}

int Bunny::getAge()
{
    return age;
}

void Bunny::setOneMoreYear()
{
    age++;
}

void Bunny::getAll()
{
    std::cout << std::setw(12) << std::left << name << std::setw(5) << "Sex: " << Bunny::sex << "\tAge: ";
	if (Bunny::age >= 0 && Bunny::age <= 50)
        std::cout << Bunny::age << std::endl;
    else
        std::cout << "INVALID" << ".\n>>> File: " << __FILE__ << "\n>>> Line: " << __LINE__ << std::endl;
}

void Bunny::setNamesList()
{
    std::fstream file;
    file.open("Imiona.csv", std::ios::in);
    if (file.good())
    {
        std::string imie;
        file >> imie;
        namesList.push_back(imie);
    }
    else
        std::cout << "FILE ERROR! Could not load names!" << std::endl;
}

Bunny::Bunny()
{
    setNamesList();
    int randomNum = rand() % namesList.size();
    std::vector<std::string>::iterator it = namesList.begin();
    std::cout << *(it + randomNum) << std::endl;
    name = "Default";
	sex = setSex();
	age = 0;
}

Bunny::~Bunny()
{
    std::cout << "The bunny "<< name << " had just got killed!" << std::endl;
}
