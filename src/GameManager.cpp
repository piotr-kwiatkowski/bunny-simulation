#include <iostream>
#include <iomanip>   // std::setw
#include <random>
#include <fstream>   // fstream
#include "GameManager.h"
#include "Bunny.h"


int GameManager::startGame()
{
    if (!this->hasLoadedNames())
    {
        return EXIT_FAILURE;
    }

    std::list<Bunny> bunniesColony;
    this->populateColony(&bunniesColony);
    this->printColony(&bunniesColony);
    
    int i = 11;
    while (i)  // MAIN GAME LOOP
    {
        if (!this->nextTurn(&bunniesColony))
        {
            // TODO: some end printings?
            std::cout << "-- !nextTurn()\n";
            break;
        }
        i--;
    }
    return EXIT_SUCCESS;
}

bool GameManager::hasLoadedNames()
{
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
    // TODO: add commentary
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, this->NAMES.size());
    return NAMES[distribution(gen)];
}

std::string GameManager::getRandomSex() const
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, 1);
    return this->SEX[distribution(gen)];
}

std::string GameManager::getRandomColor() const
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, COLORS_NR - 1);
    return this->COLORS[distribution(gen)];
}

bool GameManager::isBunnyRadioactive() const
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, 99);
    int tmp = distribution(gen);
    if (tmp > 1)  // why?
    {
        return false;
    }
    std::cout << "\n>>>>>>>>>> MUTANT !!!!!!!!\n";
    return true;
}

void GameManager::populateColony(std::list<Bunny> *a_colony)
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
        (*a_colony).push_back(newBunny);
    }
}

void GameManager::printColony(std::list<Bunny> *colony) const
{
    std::cout << "------------------------------------------------\n"
        << std::setw(10) << "NAME" << "\t"
        << "SEX\t"
        << "AGE\t"
        << "COLOR\t"
        << "MUTANT\n------------------------------------------------\n";

    for (auto const &it : *colony)
    {
        std::cout << std::setw(10)
            << it.getName()  << "\t"
            << it.getSex()   << "\t"
            << it.getAge()   << "\t"
            << it.getColor() << "\t"
            << std::boolalpha << it.getIsMutant() 
            << std::noboolalpha << '\n';
    }
    std::cout << "------------------------------------------------\n" << std::endl;
}

bool GameManager::nextTurn(std::list<Bunny> *colony)
{
    incrementColonyAge(colony);
    killElders(colony);
	infect(colony);

    breed(colony);
	
	// sort colony by age
	(*colony).sort([](Bunny a, Bunny b) { return a.getAge() < b.getAge(); });
    printColony(colony);

    if ((*colony).empty() || isColonyTotallyInfected(colony))
    {
        return false;
    }

    return true;
}

void GameManager::incrementColonyAge(std::list<Bunny> *colony)
{
    for (std::list<Bunny>::iterator it = (*colony).begin(); it != (*colony).end(); ++it)
    {
        it->incrementAge();
    }
}

void GameManager::killElders(std::list<Bunny> *colony)
{
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

void GameManager::breed(std::list<Bunny> *colony)
{
    int adultMale = 0;
	int adultFemale = 0;
    for (auto const &it : *colony)
    {
        if (it.getSex() == "male" && it.getAge() > 1 && !it.getIsMutant())
        {
            adultMale++;
			break;   // one adult male sufficient to breed
        }
    }

    if (!adultMale) {
        return;
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
}

void GameManager::infect(std::list<Bunny>* colony)
{
	int infected = 0;
	for (auto const &it : *colony)
	{
		if (it.getIsMutant())
		{
			infected++;
		}
	}

	for (int i = 0; i < infected; ++i)
	{
		// TODO:
		// choose random int N = [1 : colony.size()-1]
		// access Nth non-mutant node and change to mutant
	}
}

bool GameManager::isColonyTotallyInfected(std::list<Bunny>* colony)
{
	int infected = 0;
	return false;
}
