#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include <list>
#include "Bunny.h"

class GameManager
{
public:
    int startGame();

private:
    const std::string COLORS[4]  = { "white", "brown", "black", "spotted" };
    const std::string SEX[2]     = { "male", "female" };
    const int INITIAL_RABBITS_NR = 5;
    const int COLORS_NR          = 4;  // rename
    const int INITIAL_AGE        = 0;
    const int FAILURE            = 666;
    
    std::vector<std::string> NAMES;

    // populate initial colony
    void populateColony(std::list<Bunny> *colony);
    
    void printColony(std::list<Bunny> *colony) const;

    // returns random name from .csv file
    std::string getRandomName() const;

    // returns random sex from SEX[]
    std::string getRandomSex() const;

    // returns random color from COLORS[]
    std::string getRandomColor() const;

    // returns true with 2% chance
    bool isBunnyRadioactive() const;

    // loads bunny names from .csv file, returns true if loaded
    bool hasLoadedNames();

    // next game turn
    bool nextTurn(std::list<Bunny> *colony);

    // add 1 year to age of every rabbit in colony
    void incrementColonyAge(std::list<Bunny> *colony);

    // kill elder rabbits
    void killElders(std::list<Bunny> *colony);

    void breed(std::list<Bunny> *colony);
};

#endif // GAMEMANAGER_H

