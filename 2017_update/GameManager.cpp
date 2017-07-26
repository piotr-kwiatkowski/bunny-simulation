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

	while (true)  // MAIN GAME LOOP
	{
		if (!this->nextTurn(&bunniesColony))
		{
			// TODO: some end printings?
            std::cout << "-- !nextTurn()\n";
			break;
		}
	}
	return EXIT_SUCCESS;
}

/********************************************************************************
                         INITIAL FUNCTIONS
*********************************************************************************/
bool GameManager::hasLoadedNames()
{
    std::fstream f;
    //f.open("D:\\IT\\git-repos\\Graduation\\2017_update\\names.csv", std::ios::in);      // HOME
    f.open("D:\\_private\\git-repos\\Graduation\\2017_update\\names.csv", std::ios::in);  // OFFICE
                                                                                          //f.open("names.csv", std::ios::in);                                                  // FINAL
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
    /*int tmp = distribution(gen);
    std::cout << NAMES[tmp] << std::endl;
    return NAMES[tmp];*/
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

	for (std::list<Bunny>::iterator it = (*colony).begin(); it != (*colony).end(); ++it)
	{
		std::cout << std::setw(10)
			<< it->getName()  << "\t"
			<< it->getSex()   << "\t"
			<< it->getAge()   << "\t"
			<< it->getColor() << "\t"
			<< std::boolalpha << it->getIsRadioactiveVampireMutant() << std::noboolalpha << '\n';
	}

	std::cout << "------------------------------------------------\n" << std::endl;
}

/*********************************************************************************/


bool GameManager::nextTurn(std::list<Bunny> *colony)
{
    std::cout << "-- next year!\n";

    incrementColonyAge(colony);
    killElders(colony);

    printColony(colony);

    if ((*colony).empty())
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
    for (std::list<Bunny>::iterator it = (*colony).begin(); it != (*colony).end(); ++it)
    {
        if (it->getIsRadioactiveVampireMutant() && it->getAge() >= 50)
        {
            //(*colony).remove((*it));   // FIXME !!!
        }
        else if ((*it).getAge() >= 10)
        {
            //(*colony).remove((*it));   // FIXME !!!
        }
    }
}
