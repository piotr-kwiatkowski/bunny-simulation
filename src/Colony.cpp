#include <iostream>
#include <iomanip>   // std::setw
#include <random>
#include <fstream>   // fstream
#include <thread>    // std::this_thread::wait_for
#include <chrono>    // std::chrono::milliseconds
#include <windows.h>

#include "Colony.h"

Colony::Colony() 
    : m_malesCtr(0), m_femalesCtr(0), m_kidsCtr(0), m_mutantsCtr(0)
{
}

Colony::~Colony()
{
}

bool Colony::isColonyEmpty() const
{
    //std::cout << "-- bunnies list size: " << this->m_bunniesList.size() << "\n";
    if (this->m_bunniesList.size())
    {
        return false;
    }
    return true;
    //return !this->m_bunniesList.size();
}

bool Colony::hasLoadedNames()
{
    std::fstream f;
    f.open("src/names.csv", std::ios::in);
    if (!f.good())
    {
        std::cout << "Error opening names file!\n";
        return false;
    }

    while (f.good())
    {
        std::string tmpName;
        std::getline(f, tmpName);
        this->NAMES.push_back(tmpName);
    }
    return true;
}

std::string Colony::getRandomName() const
{
    // TODO: add commentary
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, static_cast<int>(this->NAMES.size())-1);
    return NAMES[distribution(gen)];
}

std::string Colony::getRandomSex() const
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, 1);
    return this->SEX[distribution(gen)];
}

std::string Colony::getRandomColor() const
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, COLORS_NR - 1);
    return this->COLORS[distribution(gen)];
}

bool Colony::isBunnyRadioactive() const
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, 99);
    int tmp = distribution(gen);
    if (tmp > 1)  // why?
    {
        return false;
    }
    
    return true;
}

void Colony::populateColony()
{
    for (int i = 0; i < INITIAL_RABBITS_NR; ++i)
    {
        Bunny newBunny(
            this->getRandomName(),
            this->getRandomSex(),
            this->getRandomColor(),
            INITIAL_AGE,
            this->isBunnyRadioactive()
        );

        newBunny.isMutant() ? this->m_mutantsCtr++ : this->m_kidsCtr++;
        this->m_bunniesList.push_back(newBunny);
    }
}

void Colony::print() const
{
    const int8_t BORDER = 81,
                 LWIDTH = 11,
                 SWIDTH = 4;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    std::cout << std::setw(BORDER) << std::setfill('-') << "\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << std::setw(LWIDTH + SWIDTH + 7) << std::setfill('-') << "\n"
        << "|  " << std::setfill(' ');
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    std::cout
        << std::setw(LWIDTH) << std::left << "Males:"
        << std::setw(SWIDTH) << std::right << this->m_malesCtr;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << "  |\n|  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    std::cout
        << std::setw(LWIDTH) << std::left << "Females:"
        << std::setw(SWIDTH) << std::right << this->m_femalesCtr;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << "  |\n|  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    std::cout
        << std::setw(LWIDTH) << std::left << "Kids: "
        << std::setw(SWIDTH) << std::right << this->m_kidsCtr;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << "  |\n|  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    std::cout
        << std::setw(LWIDTH) << std::left << "Mutants: "
        << std::setw(SWIDTH) << std::right << this->m_mutantsCtr;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << "  |\n"
        << std::setw(LWIDTH + SWIDTH + 7) << std::setfill('-') << "\n";
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void Colony::incrementAge()
{
    std::list<Bunny>::iterator it;
    for (it = this->m_bunniesList.begin(); it != this->m_bunniesList.end(); ++it)
    //for (auto const& it : this->m_bunniesList)
    {
        it->incrementAge();
        if (it->getAge() == ADULT_AGE)
        {
            this->m_kidsCtr--;
            it->getSex() == "male" ? this->m_malesCtr++ : this->m_femalesCtr++;
        }
    }
}

void Colony::killElders()
{
    // NOTE: iterating over list with erasing!
    std::list<Bunny>::iterator it = this->m_bunniesList.begin();
    while(it != this->m_bunniesList.end())
    {
        if (it->isMutant() && it->getAge() > DEATH_AGE_MUTANT)
        {
            it = this->m_bunniesList.erase(it);
        }
        else if ((*it).getAge() > DEATH_AGE_ADULT)
        {
            it = this->m_bunniesList.erase(it);
        }
        else {
            it++;
        }
    }
}

bool Colony::breed()
{    
    if (!this->getMalesCtr() || !this->getFemalesCtr())
    {
        return false;
    }
    
    int16_t newMutants = 0;
    int16_t maxBunniesToBreed = this->getFemalesCtr();
    std::list<Bunny> offspring; // TODO: why not using original list?
    for (std::list<Bunny>::iterator it = this->m_bunniesList.begin(); it != this->m_bunniesList.end(); ++it)
    {
        if (!maxBunniesToBreed)
        {
            break;
        }

        if (it->getSex() == "female" && it->getAge() > ADULT_AGE && !it->isMutant())
        {
            Bunny newBunny(
                this->getRandomName(),
                this->getRandomSex(),
                it->getColor(),
                INITIAL_AGE,
                this->isBunnyRadioactive()
            );
            if (newBunny.isMutant())
            {
                newMutants++;
            }
            offspring.push_back(newBunny);
        }
        else
        {
            continue;
        }

        maxBunniesToBreed--;
    }

    // adding offspring list to colony list
    this->m_kidsCtr += (offspring.size() - newMutants);
    this->m_mutantsCtr += newMutants;
    this->m_bunniesList.splice(this->m_bunniesList.end(), offspring);
    return true;
}

void Colony::infect()
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    int16_t mutantsLeft = this->m_mutantsCtr;
    while (mutantsLeft--)
    {
        if (isColonyTotallyInfected())
        {
            std::cout << "-- COLONY TOTALLY INFECTED!\n";
            break;
        }

        std::uniform_int_distribution<> dis(0, this->m_bunniesList.size()-1);
        int rnd = dis(gen);
        std::list<Bunny>::iterator it = this->m_bunniesList.begin(); 
        std::advance(it, rnd);
        if (it->isMutant())
        {
            mutantsLeft++;
        }
        else
        {
            it->convertToMutant();
            it->getSex() == "male" ? this->m_malesCtr-- : this->m_femalesCtr--;
            this->m_mutantsCtr++;
        }
    }
}

bool Colony::isColonyTotallyInfected() const
{
    if (this->m_mutantsCtr == this->m_bunniesList.size())
    {
        std::cout << "ALL BUNNIES ARE MUTANTS!\n";
        return true;
    }

    return false;
}

void Colony::performCull()
{
    throw std::logic_error("cull not implemented!");
}

int16_t Colony::getMalesCtr() const
{
    return this->m_malesCtr;
}

int16_t Colony::getFemalesCtr() const
{
    return this->m_femalesCtr;
}

int16_t Colony::getKidsCtr() const
{
    return this->m_kidsCtr;
}

int16_t Colony::getMutantsCtr() const
{
    return this->m_mutantsCtr;
}
