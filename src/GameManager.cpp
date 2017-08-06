#include <iostream>
#include <iomanip>   // std::setw
#include <random>
#include <fstream>   // fstream
#include <thread>    // std::this_thread::wait_for
#include <chrono>    // std::chrono::milliseconds
#include <Windows.h>

#include "GameManager.h"
#include "Bunny.h"

#define __PRETTY_FUNCTION__ __FUNCTION__":" << __LINE__

int8_t GameManager::startGame()
{
    if (!this->hasLoadedNames())
    {
        return EXIT_FAILURE;
    }

    std::list<Bunny> bunniesColony;
    this->populateColony(&bunniesColony);
    this->printColony(&bunniesColony);
    
    //========================================================================
    //            MAIN GAME LOOP
    //========================================================================
    int16_t rescueCntr = 0;
    int16_t res = 0;
    while (true)
    {
        // iteration every 1 second
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (!this->nextYear(&bunniesColony))
        {
            break;
        }
        
        if (++rescueCntr > 1000)
        {
            std::cout << "-- max rescue counter approached !\n";
            return 66;
        }
        
        while (true)
        {
            res = GetAsyncKeyState(VK_SPACE);
            if ((0x80000000 & res != 0) || (0x00000001 & res != 0))
            {
                continue;
            }
            else
            {
                break;
            }
        }
    }
    //========================================================================
    return EXIT_SUCCESS;
}

bool GameManager::hasLoadedNames()
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    std::fstream f;
    f.open("names.csv", std::ios::in);
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

std::string GameManager::getRandomName() const
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    // TODO: add commentary
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, this->NAMES.size()-1);
    //std::cout << "-- ==============================\n";
    return NAMES[distribution(gen)];
}

std::string GameManager::getRandomSex() const
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, 1);
    return this->SEX[distribution(gen)];
}

std::string GameManager::getRandomColor() const
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, COLORS_NR - 1);
    return this->COLORS[distribution(gen)];
}

bool GameManager::isBunnyRadioactive() const
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

void GameManager::populateColony(std::list<Bunny> *a_colony)
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
        (*a_colony).push_back(newBunny);
    }
}

void GameManager::printColony(std::list<Bunny> *colony) const
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "---------------------------------------------------------------\n"
        << std::setw(20) << "NAME" << "\t"
        << "SEX\t"
        << "AGE\t"
        << "COLOR\t"
        << "MUTANT\n-------------------------------------------------------------\n";

    for (auto const &it : *colony)
    {
        std::cout << std::setw(20)
            << it.getName()  << "\t"
            << it.getSex()   << "\t"
            << it.getAge()   << "\t"
            << it.getColor() << "\t"
            << std::boolalpha << it.getIsMutant() 
            << std::noboolalpha << '\n';
    }
    std::cout << "----------------------------------------------------------------\n" << std::endl;
}

bool GameManager::nextYear(std::list<Bunny> *colony)
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

void GameManager::incrementColonyAge(std::list<Bunny> *colony)
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    for (std::list<Bunny>::iterator it = (*colony).begin(); it != (*colony).end(); ++it)
    {
        it->incrementAge();
    }
}

void GameManager::killElders(std::list<Bunny> *colony)
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    // NOTE: iterating over list with erasing!
    std::list<Bunny>::iterator it = (*colony).begin();
    while(it != (*colony).end())
    {
        if (it->getIsMutant() && it->getAge() >= 50)
        {
            it = (*colony).erase(it);
        }
        else if ((*it).getAge() >= 10)
        {
            it = (*colony).erase(it);
        }
        else {
            it++;
        }
    }
}

bool GameManager::breed(std::list<Bunny> *colony)
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    int adultMales   = 0;
    int adultFemales = 0;
    int children     = 0;
    for (auto const &it : *colony)
    {
        if (it.getSex() == "male" && it.getAge() > 1 && !it.getIsMutant())
        {
            adultMales++;
        }
        else if (it.getSex() == "female" && it.getAge() > 1 && !it.getIsMutant())
        {
            adultFemales++;
        }
        else if (!it.getIsMutant())
        {
            children++;
        }
    }

    if (!adultMales && !children) {
        std::cout << "NO ADULT MALES\n";
        return false;
    }
    else if (!adultFemales && !children)
    {
        std::cout << "NO ADULT FEMALES!\n";
        return false;
    }
    
    std::list<Bunny> offspring;
    for (auto const &it : *colony) 
    {
        if (it.getSex() == "female" && it.getAge() > 1 && !it.getIsMutant())
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

void GameManager::infect(std::list<Bunny>* colony)
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    int infected = 0;
    for (auto const &it : *colony)
    {
        if (it.getIsMutant())
        {
            infected++;
        }
    }

    //std::cout << "-- infected: " << infected << std::endl;
    int colSize = (*colony).size();
    std::random_device rd;
    std::mt19937_64 gen(rd());
    for (int i = 0; i < infected; ++i)
    {
        if (isColonyTotallyInfected(colony))
        {
            //std::cout << "-- no infecting possible!\n";
            break;
        }

        std::uniform_int_distribution<> distribution(0, colSize-1);
        int rnd = distribution(gen);
        //std::cout << "-- colSize: " << colSize << "\trnd: " << rnd << std::endl;
        std::list<Bunny>::iterator it = (*colony).begin();
        std::advance(it, rnd);

        if ((*it).getIsMutant())
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

bool GameManager::isColonyTotallyInfected(std::list<Bunny>* colony)
{
    //std::cout << "-- " << __PRETTY_FUNCTION__ << std::endl;
    int infected = 0;
    for (auto const &it : *colony)
    {
        if (it.getIsMutant())
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
