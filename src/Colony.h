#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include <list>
#include "Bunny.h"

class Colony
{
public:
    std::list<Bunny> m_colony;

    // loads bunny names from .csv file, returns true if loaded
    bool hasLoadedNames();

    // populate initial colony
    void populateColony();

    void printColony() const;

    // add 1 year to age of every rabbit in colony
    void incrementColonyAge();

    // kill elder rabbits
    void killElders();

    bool breed();

    // infect colony if mutant(s) present
    void infect();

    // check if all colony is mutant positive
    bool isColonyTotallyInfected() const;

private:
    const std::string COLORS[4]  = { "white", "brown", "black", "spotted" };
    const std::string SEX[2]     = { "male", "female" };
    const int8_t INITIAL_RABBITS_NR = 5;
    const int8_t COLORS_NR          = 4;  // rename
    const int8_t INITIAL_AGE        = 0;
    const int8_t FAILURE            = 66;
    
    std::vector<std::string> NAMES;
    
    int16_t males   = 0;
    int16_t females = 0;
    int16_t kids    = 0;
    int16_t mutants = 0;

    // returns random name from .csv file
    std::string getRandomName() const;

    // returns random sex from SEX[]
    std::string getRandomSex() const;

    // returns random color from COLORS[]
    std::string getRandomColor() const;

    // returns true with 2% chance
    bool isBunnyRadioactive() const;

};

#endif // GAMEMANAGER_H

