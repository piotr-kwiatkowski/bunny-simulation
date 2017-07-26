/*
	2017 UPDATE for Graduation project

	Started: 13-03-2017

 */


#include <iostream>
#include "GameManager.h"

int main(int argc, char const *argv[])
{
	GameManager oGameManager;
	oGameManager.startGame();

    std::cout << "\nPress enter to close program...";
	std::cin.ignore();

	return 0;
}