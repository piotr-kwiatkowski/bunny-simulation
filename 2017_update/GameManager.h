#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>

class GameManager
{
public:
	int StartGame();

private:
	const std::string COLORS[4] = { "white", "brown", "black", "spotted" };
	const std::string SEX[2]    = { "male", "female" };
	const int INITIAL_RABBITS_NR = 5;
	const int COLORS_NR   = 4;  // rename
	const int INITIAL_AGE = 0;
	const int FAILURE = 666;
	std::vector<std::string> NAMES;

	// populate initial colony
	void populateColony(std::vector<Bunny> *colony);
	
	void printColony(std::vector<Bunny> *colony);

	// returns random name from .csv file
	std::string getRandomName();

	// returns random sex from SEX[]
	std::string getRandomSex();

	// returns random color from COLORS[]
	std::string getRandomColor();

	// returns true with 2% chance
	bool isBunnyRadioactive();

	// loads bunny names from .csv file
	bool loadNamesFromFile();

	// next game turn
	int nextTurn();
};

#endif // GAMEMANAGER_H

