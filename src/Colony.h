#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include <list>
#include "Bunny.h"

class Colony
{
public:

// private:
    const std::string COLORS[4]  = { "white", "brown", "black", "spotted" };
    const std::string SEX[2]     = { "male", "female" };
    const int8_t INITIAL_RABBITS_NR = 5;
    const int8_t COLORS_NR          = 4;  // rename
    const int8_t INITIAL_AGE        = 0;
    const int8_t FAILURE            = 66;
    
    int16_t males   = 0;
    int16_t females = 0;
    int16_t kids    = 0;
    int16_t mutants = 0;

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
    bool nextYear(std::list<Bunny> *colony);

    // add 1 year to age of every rabbit in colony
    void incrementColonyAge(std::list<Bunny> *colony);

    // kill elder rabbits
    void killElders(std::list<Bunny> *colony);

    bool breed(std::list<Bunny> *colony);

    // infect colony if mutant(s) present
    void infect(std::list<Bunny> *colony);

    // check if all colony is mutant positive
    bool isColonyTotallyInfected(std::list<Bunny> *colony);
};

#endif // GAMEMANAGER_H

