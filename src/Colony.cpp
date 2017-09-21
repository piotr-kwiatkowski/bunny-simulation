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

void Colony::populateColony(std::list<Bunny> *a_colony)
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    for (int i = 0; i < INITIAL_RABBITS_NR; ++i)
    {
        Bunny newBunny(
            this->getRandomName(),
            this->getRandomSex(),
            this->getRandomColor(),
            INITIAL_AGE,
            this->isBunnyRadioactive()
        );
        if (newBunny.isMutant())
        {
            this->mutants++;
        }
        else
        {
            this->kids++;
        }
        (*a_colony).push_back(newBunny);
    }
}

void Colony::printColony(std::list<Bunny> *colony) const
{
    /*int16_t males   = 0;
    int16_t females = 0;
    int16_t vamps   = 0;
    for (auto const &it : *colony)
    {
        if (it.getIsMutant())
        {
            vamps++;
            continue;
        }

        if (it.getSex() == "male")
        {
            males++;
        }
        else if (it.getSex() == "female")
        {
            females++;
        }
    }*/
    
    std::cout << "Adults\t* males: " << this->males
              << "\t\t* females: "   << this->females
              << "Kids: "            << this->kids
              << "Mutants: "         << this->mutants
              << "\n";

    /*
    std::cout << "---------------------------------------------------------------\n"
        << std::setw(20) << "NAME" << "\t"
        << "SEX\t"
        << "AGE\t"
        << "COLOR\t"
        << "MUTANT\n-------------------------------------------------------------\n";

    for (auto const &it : *colony)
    {
        std::cout << it << '\n';
    }
    std::cout << "----------------------------------------------------------------\n" << std::endl;*/
}

bool Colony::nextYear(std::list<Bunny> *colony)
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    incrementColonyAge(colony);
    killElders(colony);
    //infect(colony);
    
    if (!breed(colony))
    {
        std::cout << "COLONY CAN NOT BREED!\n";
        return false;
    }
    
    // sort colony by age
    (*colony).sort([](Bunny a, Bunny b) { return a.getAge() > b.getAge(); });  // TODO: move it to function
    printColony(colony);
    
    if ((*colony).empty() || isColonyTotallyInfected(colony))
    {
        //std::cout << "-- nextturn false\n";
        return false;
    }
    
    //std::cout << "-- nextturn true\n";
    return true;
}

void Colony::incrementColonyAge(std::list<Bunny> *colony)
{
    for (std::list<Bunny>::iterator it = (*colony).begin(); it != (*colony).end(); ++it)
    {
        it->incrementAge();
        if (it->getAge() > 1)
        {
            this->kids--;
            it->getSex() == "male" ? this->males++ : this->females++;
        }
    }
}

void Colony::killElders(std::list<Bunny> *colony)
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    // NOTE: iterating over list with erasing!
    std::list<Bunny>::iterator it = (*colony).begin();
    while(it != (*colony).end())
    {
        if (it->isMutant() && it->getAge() > 50)
        {
            it = (*colony).erase(it);
        }
        else if ((*it).getAge() > 10)
        {
            it = (*colony).erase(it);
        }
        else {
            it++;
        }
    }
}

bool Colony::breed(std::list<Bunny> *colony)
{    
    if (!this->males || !this->females)
    {
        std::cout << "NO ADULT PAIRS!\n";
        return false;
    }

    std::list<Bunny> offspring;
    for (auto const &it : *colony)
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
    (*colony).splice((*colony).end(), offspring);
    return true;
}

void Colony::infect(std::list<Bunny>* colony)
{
    int colSize = (*colony).size();
//    int colSize = this->
    std::random_device rd;
    std::mt19937_64 gen(rd());
    for (int i = 0; i < this->mutants; ++i)
    {
        if (isColonyTotallyInfected(colony))
        {
            std::cout << "-- COLONY TOTALLY INFECTED!\n";
            break;
        }

        std::uniform_int_distribution<> distribution(0, colSize-1);
        int rnd = distribution(gen);
        //std::cout << "-- colSize: " << colSize << "\trnd: " << rnd << std::endl;
        std::list<Bunny>::iterator it = (*colony).begin();
        std::advance(it, rnd);

        if ((*it).isMutant())
        {
            //std::cout << "\t-- already infected!\n";
            i--;
            continue;
        }
        else
        {
            (*it).convertToMutant();
        }
    }
}

bool Colony::isColonyTotallyInfected(std::list<Bunny>* colony)
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    int infected = 0;
    for (auto const &it : *colony)
    {
        if (it.isMutant())
        {
            infected++;
        }
    }

    if (infected == (*colony).size())
    {
        std::cout << "ALL BUNNIES ARE MUTANTS!\n";
        return true;
    }

    return false;
}
