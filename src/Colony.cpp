#pragma once
#include <iostream>
#include <iomanip>   // std::setw
#include <random>
#include <fstream>   // fstream
#include <thread>    // std::this_thread::wait_for
#include <chrono>    // std::chrono::milliseconds
#include <windows.h>
#include <vector>

#include "Colony.h"
#include "GameManager.h"

const size_t GRID_HEIGHT = 51; // FIXME: this is a duplicated const

Colony::Colony() 
    : m_malesCtr(0), m_femalesCtr(0), m_kidsCtr(0), m_mutantsCtr(0)
{
}

Colony::~Colony()
{
}

bool Colony::isColonyEmpty() const
{
    if (getColonySize())
    {
        return false;
    }
    return true;
    //return !getColonySize();
}

bool Colony::hasLoadedNames()
{
    std::fstream f;
    f.open("src/names.csv", std::ios::in);
    if (!f.good())
    {
        std::cout << "Error opening names file!" << std::endl;;
        return false;
    }

    while (f.good())
    {
        std::string tmpName;
        std::getline(f, tmpName);
        NAMES.push_back(tmpName);
    }
    return true;
}

std::string Colony::getRandomName() const
{
    // TODO: add commentary
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, static_cast<int>(NAMES.size())-1);
    return NAMES[distribution(gen)];
}

std::string Colony::getRandomSex() const
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, 1);
    return SEX[distribution(gen)];
}

std::string Colony::getRandomColor() const
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, COLORS_NR - 1);
    return COLORS[distribution(gen)];
}

bool Colony::isBunnyRadioactive() const
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, 99);
    int tmp = distribution(gen);
    return tmp > 98;
}

void Colony::initColony()
{
    int8_t males = 0, females = 0; // ?
    for (int i = 0; i < INITIAL_RABBITS_NR; ++i)
    {
        Bunny newBunny(
            getRandomName(),
            getRandomSex(),
            getRandomColor(),
            INITIAL_AGE,  // FIXME: age should be random 0-10 years
            false         // FIXME: where's the 2% chance of a mutant? no initial mutants?
        );

        if (m_kidsCtr == INITIAL_RABBITS_NR-1 && (males || females)) // wtf is this if? xD
        {
            i--; // wtf? why decrementing during iteration?
            continue;
        }
        m_kidsCtr++; // xD LOL
        m_bunniesList.push_back(newBunny);
    }

    // DEBUGGING:
    GameManager oGM;
    oGM.moveCursorTo(0, GRID_HEIGHT + 2);
    std::cout << "--- m_kidsCtr: " << m_kidsCtr << std::endl;
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
        << std::setw(SWIDTH) << std::right << m_malesCtr;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << "  |\n|  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    std::cout
        << std::setw(LWIDTH) << std::left << "Females:"
        << std::setw(SWIDTH) << std::right << m_femalesCtr;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << "  |\n|  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    std::cout
        << std::setw(LWIDTH) << std::left << "Kids: "
        << std::setw(SWIDTH) << std::right << m_kidsCtr;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << "  |\n|  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    std::cout
        << std::setw(LWIDTH) << std::left << "Mutants: "
        << std::setw(SWIDTH) << std::right << m_mutantsCtr;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << "  |\n"
        << std::setw(LWIDTH + SWIDTH + 7) << std::setfill('-') << "\n";
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void Colony::incrementAge()
{
    std::list<Bunny>::iterator it;
    for (it = m_bunniesList.begin(); it != m_bunniesList.end(); ++it)
    {
        it->incrementAge();

        // check if bunny is an adult
        if (!it->isMutant() && it->getAge() == ADULT_AGE)
        {
            m_kidsCtr--;
            it->getSex() == "male" ? m_malesCtr++ : m_femalesCtr++;
        }
    }

    // DEBUGGING:
    GameManager oGM;
    oGM.moveCursorTo(0, GRID_HEIGHT + 1);
    std::cout << "--- bunnies age incremented" << std::endl;
}

void Colony::killElders()
{
    size_t initSize = getColonySize();
    //size_t killCtr = 0;
    // NOTE: iterating over list with erasing!
    std::list<Bunny>::iterator it = m_bunniesList.begin();
    while(it != m_bunniesList.end())
    {
        // if bunny is mutant and above 50 yo
        if (it->isMutant() && it->getAge() > DEATH_AGE_MUTANT)
        {
            it = m_bunniesList.erase(it);
            m_mutantsCtr--;
            //killCtr++;
            continue;
        }
        // if bunny is not a mutant and above age 10
        else if (!it->isMutant() && it->getAge() > DEATH_AGE_ADULT)
        {
            it->getSex() == "male" ? m_malesCtr-- : m_femalesCtr--;
            it = m_bunniesList.erase(it);
            //killCtr++;
        }
        else {
            it++;
        }
    }

    // test
    //size_t endSize = getColonySize();
    //if (initSize - endSize != killCtr)
    //{
    //    std::cout << "--- kill counter error!" << std::endl;;  // TODO: print to error log file
    //    std::cin.get();
    //}
}

bool Colony::breed()
{
    if (!getAdultMalesCtr() || !getAdultFemalesCtr())
    {
        return false;
    }
    
    size_t newMutants = 0;
    size_t maxBunniesToBreed = getAdultFemalesCtr();
    std::list<Bunny> offspring;
    // FIXME: this could be a simple loop creating new bunnies
    for (std::list<Bunny>::iterator it = m_bunniesList.begin(); it != m_bunniesList.end(); ++it)
    {
        if (it->isMutant())
        {
            continue;
        }
        else if (it->getSex() == "female" && it->getAge() > ADULT_AGE)
        {
            Bunny newBunny(
                getRandomName(),
                getRandomSex(),
                it->getColor(),
                INITIAL_AGE,
                isBunnyRadioactive()
            );
            if (newBunny.isMutant())
            {
                m_mutantsCtr++;
            }
            else
            {
                m_kidsCtr++;
            }
            offspring.push_back(newBunny);
        }
        else
        {
            continue;
        }
    }

    // adding offspring list to colony list
    m_bunniesList.splice(m_bunniesList.end(), offspring);
    return true;
}

// infect random bunnies
void Colony::infect()
{
    //std::cout << "now infect " << std::endl;

    std::random_device rd;     // a seed source for the random number engine
    std::mt19937_64 gen(rd()); // mersenne_twister_engine seeded with rd()
    size_t mutantsToCreate = m_mutantsCtr;
    std::vector<size_t> prevDists;

    // DEBUGGING:
    GameManager oGM;
    oGM.moveCursorTo(0, GRID_HEIGHT + 3);
    std::cout << "--- colony size: " << getColonySize() << std::endl;

    while (mutantsToCreate--)
    {
        if (isColonyTotallyInfected())
        {
            break; // FIXME: any msg?
            std::cout << "--- colony is totally infected" << std::endl;
        }

        std::uniform_int_distribution<> distribution(0, static_cast<int>(getColonySize()) - 1); // FIXME?: wtf is this doing? why -1 after closing parenthesis? this static_cast seems redundant
        size_t currentDist = distribution(gen);
        if (std::find(std::begin(prevDists), std::end(prevDists), currentDist) != std::end(prevDists)) // wtf is here happening?
        {
            continue;
        }
        else
        {
            prevDists.push_back(currentDist);
        }

        std::list<Bunny>::iterator it = m_bunniesList.begin();
        std::advance(it, currentDist);  // increment it by rnd distance -- bad idea when list is huge
        if (it->isMutant() || it->getAge() < ADULT_AGE)
        {
            mutantsToCreate++;
        }
        else
        {
            it->convertToMutant();
            if (it->getAge() >= ADULT_AGE)
            {
                it->getSex() == "male" ? m_malesCtr-- : m_femalesCtr--;
            }
            m_mutantsCtr++;
        }
    }
}

bool Colony::isColonyTotallyInfected() const
{
    return m_mutantsCtr >= getColonySize();
}

void Colony::performDeathByStarvation()
{
    throw std::logic_error("Death by starvation has not been implemented yet!");
}

size_t Colony::getColonySize() const
{
    return m_bunniesList.size();
}

size_t Colony::getAdultMalesCtr() const
{
    return m_malesCtr;
}

size_t Colony::getAdultFemalesCtr() const
{
    return m_femalesCtr;
}

size_t Colony::getKidsCtr() const
{
    return m_kidsCtr;
}

size_t Colony::getMutantsCtr() const
{
    return m_mutantsCtr;
}
