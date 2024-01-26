#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include <list>
#include "Bunny.h"

class Colony
{
public:
    Colony();
    ~Colony();

    std::list<Bunny> m_bunniesList;

    bool isColonyEmpty() const;

    // loads bunny names from .csv file, returns true if loaded
    bool hasLoadedNames();

    // populate colony with initial 5 bunnies
    void initColony();

    // TODO: this method should mbe moved to Manager class
    void print() const;

    // increment age of every rabbit in colony
    // increment adults counter and decrement kids counter if necessary
    void incrementAge();

    // kill elder bunnies
    void killElders();

    // if there is one male >= 2 years old, every female bunny >= 2 years old breeds 1 bunny ()
    bool breed();

    // infect colony if mutant(s) present
    void infect();

    // check if all colony is mutant positive
    bool isColonyTotallyInfected() const;

    // kill half of the bunnies in the colony, randomly chosen
    void performDeathByStarvation();

    // getters
    size_t getColonySize() const;
    size_t getAdultMalesCtr() const;
    size_t getAdultFemalesCtr() const;
    size_t getKidsCtr() const;
    size_t getMutantsCtr() const;

private:
    const std::string COLORS[4]  = { "white", "brown", "black", "spotted" };
    const std::string SEX[2]     = { "male", "female" };
    const int8_t INITIAL_RABBITS_NR = 5;
    const int8_t COLORS_NR          = 4;  // rename
    const int8_t INITIAL_AGE        = 0;
    const int8_t FAILURE            = 66;
    
    const int8_t ADULT_AGE = 5;

    const int8_t DEATH_AGE_MUTANT = 50;
    const int8_t DEATH_AGE_ADULT  = 10; // shouldn't this be 10?

    
    std::vector<std::string> NAMES;
    
    size_t m_malesCtr   = 0;
    size_t m_femalesCtr = 0;
    size_t m_kidsCtr    = 0;
    size_t m_mutantsCtr = 0;

    // returns random name from .csv file
    std::string getRandomName() const;

    // returns random sex from SEX[]
    std::string getRandomSex() const;

    // returns random color from COLORS[]
    std::string getRandomColor() const;

    // returns true with 1% chance
    bool isBunnyRadioactive() const;

};

#endif // GAMEMANAGER_H

