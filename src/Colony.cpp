#include <iostream>
#include <iomanip>   // std::setw
#include <random>
#include <fstream>   // fstream
#include <thread>    // std::this_thread::wait_for
#include <chrono>    // std::chrono::milliseconds
#include <windows.h>

#include "Colony.h"

#define __PRETTY_FUNCTION__ __FUNCTION__":" << __LINE__

bool Colony::hasLoadedNames()
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
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
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    // TODO: add commentary
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, this->NAMES.size()-1);
    //std::cout << "-- ==============================\n";
    return NAMES[distribution(gen)];
}

std::string Colony::getRandomSex() const
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, 1);
    return this->SEX[distribution(gen)];
}

std::string Colony::getRandomColor() const
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, COLORS_NR - 1);
    return this->COLORS[distribution(gen)];
}

bool Colony::isBunnyRadioactive() const
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, 99);
    int tmp = distribution(gen);
    if (tmp > 1)  // why?
    {
        return false;
    }
    
    //std::cout << "\n>>>>>>>>>> MUTANT !!!!!!!!\n";
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

        newBunny.isMutant() ? this->mutants++ : this->kids++;
        this->m_colony.push_back(newBunny);
    }
}

void Colony::printColony() const
{
    std::cout << "Adults\t* males: " << this->males
              << "\t\t* females: "   << this->females
              << "Kids: "            << this->kids
              << "Mutants: "         << this->mutants
              << "\n";
}

void Colony::incrementColonyAge()
{
    for (auto it : this->m_colony)
    {
        it.incrementAge();
        if (it.getAge() > 1)
        {
            this->kids--;
            it.getSex() == "male" ? this->males++ : this->females++;
        }
    }
}

void Colony::killElders()
{
    // NOTE: iterating over list with erasing!
    std::list<Bunny>::iterator it = this->m_colony.begin();
    while(it != this->m_colony.end())
    {
        if (it->isMutant() && it->getAge() > 50)
        {
            it = this->m_colony.erase(it);
        }
        else if ((*it).getAge() > 10)
        {
            it = this->m_colony.erase(it);
        }
        else {
            it++;
        }
    }
}

bool Colony::breed()
{    
    if (!this->males || !this->females)
    {
        std::cout << "NO ADULT PAIRS!\n";
        return false;
    }

    std::list<Bunny> offspring;
    for (auto it : this->m_colony)
    {
        if (it.getSex() == "female" && it.getAge() > 1 && !it.isMutant())
        {
            Bunny newBunny(
                this->getRandomName(),
                this->getRandomSex(),
                it.getColor(),
                INITIAL_AGE,
                this->isBunnyRadioactive()
            );
            offspring.push_back(newBunny);
        }
    }
    // adding offspring to colony
    this->m_colony.splice(this->m_colony.end(), offspring);
    return true;
}

void Colony::infect()
{
    int colSize = this->m_colony.size();
    std::random_device rd;
    std::mt19937_64 gen(rd());
    for (int i = 0; i < this->mutants; ++i)
    {
        if (isColonyTotallyInfected())
        {
            std::cout << "-- COLONY TOTALLY INFECTED!\n";
            break;
        }

        std::uniform_int_distribution<> distribution(0, colSize-1);
        int rnd = distribution(gen);
        std::list<Bunny>::iterator it = this->m_colony.begin(); 
        // auto it = this->colony.begin();
        std::advance(it, rnd);
        (*it).isMutant() ? i-- : (*it).convertToMutant();
    }
}

bool Colony::isColonyTotallyInfected() const
{
    if (this->mutants == this->m_colony.size())
    {
        std::cout << "ALL BUNNIES ARE MUTANTS!\n";
        return true;
    }

    return false;
}
