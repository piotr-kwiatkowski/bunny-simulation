#include <iostream> // cout
#include <iomanip>      // std::setw
//#include <list>
#include <random>
#include <fstream>  // fstream

#include "GameManager.h"
#include "Bunny.h"


int GameManager::StartGame()
{
	if (this->loadNamesFromFile() == false)
	{
		return EXIT_FAILURE;
	}

	std::vector<Bunny> bunniesColony;
	this->populateColony(&bunniesColony);
	this->printColony(&bunniesColony);
	
	while (true)  // MAIN GAME LOOP
	{
		std::cout << "\nMAIN LOOP\n";
		if (this->nextTurn() == FAILURE)
		{
			// TODO: some end printings?
			break;
		}
	}
	return EXIT_SUCCESS;
}

void GameManager::populateColony(std::vector<Bunny> *colony)
{
	for (int i = 0; i < INITIAL_RABBITS_NR; ++i)  // TODO: move this to a function & add try/catch block
	{
		Bunny newBunny(
			this->getRandomName(),
			this->getRandomSex(),
			this->getRandomColor(),
			INITIAL_AGE,
			this->isBunnyRadioactive());
		(*colony).push_back(newBunny);
	}
}

void GameManager::printColony(std::vector<Bunny>* colony)
{
	std::cout << "------------------------------------------------\n"
		<< std::setw(10) << "NAME" << "\t"
		<< "SEX\t"
		<< "AGE\t"
		<< "COLOR\t"
		<< "MUTANT\n------------------------------------------------\n";
	for (std::vector<Bunny>::iterator it = (*colony).begin(); it != (*colony).end(); ++it)
	{
		std::cout << std::setw(10) << (*it).getName() << "\t"
			<< (*it).getSex() << "\t"
			<< (*it).getAge() << "\t"
			<< (*it).getColor() << "\t"
			<< std::boolalpha << (*it).getIsRadioactiveVampireMutant() << std::noboolalpha << '\n';
	}
	std::cout << "------------------------------------------------\n" << std::endl;
}

std::string GameManager::getRandomName()
{
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<> distribution(0, this->NAMES.size());
	int tmp = distribution(gen);
	//std::cout << NAMES[tmp] << std::endl;
	//return NAMES[distribution(gen)];
	return NAMES[tmp];
}

std::string GameManager::getRandomSex()
{
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<> distribution(0, 1);
	return this->SEX[distribution(gen)];
}

std::string GameManager::getRandomColor()
{
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<> distribution(0, COLORS_NR - 1);
	return this->COLORS[distribution(gen)];
}

bool GameManager::isBunnyRadioactive()
{
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<> distribution(0, 99);
	int tmp = distribution(gen);
	if (tmp > 1)
	{
		return false;
	}
	std::cout << "\n>>>>>>>>>> MUTANT !!!!!!!!\n";
	return true;
}

bool GameManager::loadNamesFromFile()
{
	std::fstream f;
	f.open("D:\\IT\\git-repos\\Graduation\\2017_update\\names.csv", std::ios::in);
	//f.open("D:\\_private\\git-repos\\Graduation\\2017_update\\names.csv", std::ios::in);  // <-- FIXME: relative path
	//f.open("names.csv", std::ios::in);
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

int GameManager::nextTurn()
{
	// TODO: add 1 year to every rabbit
	// TODO: check age of every rabbit, kill if too old
	return FAILURE;
}
