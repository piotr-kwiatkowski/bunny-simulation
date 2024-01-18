#include <iostream>
#include <iomanip>   // std::setw
#include <random>
#include <fstream>   // fstream
#include <thread>    // std::this_thread::wait_for
#include <chrono>    // std::chrono::milliseconds
#include <windows.h>
#include <vector>

#include "Colony.h"

Colony::Colony() 
    : m_malesCtr(0), m_femalesCtr(0), m_kidsCtr(0), m_mutantsCtr(0)
{
}

Colony::~Colony()
{
}

bool Colony::isColonyEmpty() const
{
    if (getColonySize())
    {
        return false;
    }
    return true;
    //return !getColonySize();
}

bool Colony::hasLoadedNames()
{
    std::fstream f;
    f.open("src/names.csv", std::ios::in);
    if (!f.good())
    {
        std::cout << "Error opening names file!" << std::endl;;
        return false;
    }

    while (f.good())
    {
        std::string tmpName;
        std::getline(f, tmpName);
        NAMES.push_back(tmpName);
    }
    return true;
}

std::string Colony::getRandomName() const
{
    // TODO: add commentary
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, static_cast<int>(NAMES.size())-1);
    return NAMES[distribution(gen)];
}

std::string Colony::getRandomSex() const
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, 1);
    return SEX[distribution(gen)];
}

std::string Colony::getRandomColor() const
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, COLORS_NR - 1);
    return COLORS[distribution(gen)];
}

bool Colony::isBunnyRadioactive() const
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distribution(0, 99);
    int tmp = distribution(gen);
    if (tmp > 1)  // why?
    {
        return false;
    }
    
    return true;
}

void Colony::populateColony()
{
    int8_t males = 0, females = 0; // ?
    for (int i = 0; i < INITIAL_RABBITS_NR; ++i)
    {
        Bunny newBunny(
            getRandomName(),
            getRandomSex(),
            getRandomColor(),
            INITIAL_AGE,  // FIXME: age should be random 0-10 years
            false         // FIXME: where's the 2% chance of a mutant?
        );

        if (m_kidsCtr == INITIAL_RABBITS_NR-1 && (males || females)) // ohui, pojebalo mnie z tym ifem xD
        {
            i--;
            continue;
        }
        m_kidsCtr++; // xD LOL
        m_bunniesList.push_back(newBunny);
    }

    std::cout << "\n--- m_kidsCtr: " << m_kidsCtr << std::endl;
}

void Colony::print() const
{
    const int8_t BORDER = 81,
                 LWIDTH = 11,
                 SWIDTH = 4;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    std::cout << std::setw(BORDER) << std::setfill('-') << "\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << std::setw(LWIDTH + SWIDTH + 7) << std::setfill('-') << "\n"
        << "|  " << std::setfill(' ');
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    std::cout
        << std::setw(LWIDTH) << std::left << "Males:"
        << std::setw(SWIDTH) << std::right << m_malesCtr;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << "  |\n|  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    std::cout
        << std::setw(LWIDTH) << std::left << "Females:"
        << std::setw(SWIDTH) << std::right << m_femalesCtr;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << "  |\n|  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    std::cout
        << std::setw(LWIDTH) << std::left << "Kids: "
        << std::setw(SWIDTH) << std::right << m_kidsCtr;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << "  |\n|  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    std::cout
        << std::setw(LWIDTH) << std::left << "Mutants: "
        << std::setw(SWIDTH) << std::right << m_mutantsCtr;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << "  |\n"
        << std::setw(LWIDTH + SWIDTH + 7) << std::setfill('-') << "\n";
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

// increment age of every bunny
void Colony::incrementAge()
{
    //std::cout << "now increment " << std::endl;

    //size_t initialTotalAge = 0;
    //size_t endTotalAge = 0;
    std::list<Bunny>::iterator it;
    for (it = m_bunniesList.begin(); it != m_bunniesList.end(); ++it)
    {
        //initialTotalAge += it->getAge(); // FIXME: wtf is this incrementing?
        it->incrementAge();
        //endTotalAge += it->getAge();

        if (it->getAge() == ADULT_AGE && !it->isMutant())  // so every non-mutant is breeding no matter the sex? no pairs needed?
        {
            // m_kidsCtr--; // FIXME: why? kid dies? m_kidsCtr++?
            m_kidsCtr++; // why incrementing instead of creating new Bunny object and storing in m_bunniesList? 
            // because std::list is too slow?
            it->getSex() == "male" ? m_malesCtr++ : m_femalesCtr++;
        }
    }

    std::cout << "--- bunnies age incremented" << std::endl;

    // test
    //if (endTotalAge - initialTotalAge != m_bunniesList.size())  // wtf xD co tu kurwa robi ten test? xDDD
    //{
    //    std::cout << "-- incrementing age ERROR!\n";  // TODO: print to error log file
    //    std::cin.get();
    //}

}

// kill too old bunnies
// regular bunny dies > 10 years old, mutants die at 50 years old
void Colony::killElders()
{
    //std::cout << "now kill" << std::endl;

    size_t initSize = getColonySize();
    size_t killCtr = 0;
    // NOTE: iterating over list with erasing!
    std::list<Bunny>::iterator it = m_bunniesList.begin();
    while(it != m_bunniesList.end())
    {
        if (it->isMutant() && it->getAge() > DEATH_AGE_MUTANT)
        {
            m_mutantsCtr--;
            it = m_bunniesList.erase(it);
            killCtr++;
            //std::cout << "--- mutant killed" << std::endl;
        }
        else if (!it->isMutant() && it->getAge() > DEATH_AGE_ADULT)
        {
            it->getSex() == "male" ? m_malesCtr-- : m_femalesCtr--;
            it = m_bunniesList.erase(it); // FIXME: and what is happening with "it"? is it pointing to next element?
            killCtr++;
            //std::cout << "--- bunny killed" << std::endl;
        }
        else {
            it++;
        }
    }
    size_t endSize = getColonySize();

    // test
    if (initSize - endSize != killCtr)
    {
        std::cout << "-- kill counter error!" << std::endl;;  // TODO: print to error log file
        std::cin.get();
    }
}

// if there is one male >= 2 years old, every female bunny >= 2 years old breeds 1 bunny ()
bool Colony::breed()
{
    //std::cout << "now breed" << std::endl;

    if (!getMalesCtr() || !getFemalesCtr())
    {
        return false;
    }
    
    size_t newMutants = 0;
    size_t maxBunniesToBreed = getFemalesCtr();
    if (!maxBunniesToBreed)
    {
        return false;
    }
    std::list<Bunny> offspring; // TODO: why not using original list?
    for (std::list<Bunny>::iterator it = m_bunniesList.begin(); it != m_bunniesList.end(); ++it)
    {
        if (it->getSex() == "female" && it->getAge() > ADULT_AGE && !it->isMutant())
        {
            Bunny newBunny(
                getRandomName(),
                getRandomSex(),
                it->getColor(),
                INITIAL_AGE,
                isBunnyRadioactive()
            );
            if (newBunny.isMutant())
            {
                newMutants++;
            }
            offspring.push_back(newBunny);
        }
        else
        {
            continue;
        }

        maxBunniesToBreed--;
        if (!maxBunniesToBreed)
        {
            break;
        }
    }

    // adding offspring list to colony list
    m_kidsCtr += (offspring.size() - newMutants);
    m_mutantsCtr += newMutants;
    m_bunniesList.splice(m_bunniesList.end(), offspring);
    return true;
}

// infect random bunnies
void Colony::infect()
{
    //std::cout << "now infect " << std::endl;

    std::random_device rd;     // a seed source for the random number engine
    std::mt19937_64 gen(rd()); // mersenne_twister_engine seeded with rd()
    size_t mutantsToCreate = m_mutantsCtr;
    std::vector<size_t> prevDists;

    std::cout << "--- colony size: " << getColonySize() << std::endl;

    while (mutantsToCreate--)
    {
        if (isColonyTotallyInfected())
        {
            break; // FIXME: any msg?
            std::cout << "--- colony is totally infected" << std::endl;
        }

        std::uniform_int_distribution<> distribution(0, static_cast<int>(getColonySize()) - 1); // FIXME?: wtf is this doing? why -1 after closing parenthesis? this static_cast seems redundant
        size_t currentDist = distribution(gen);
        if (std::find(std::begin(prevDists), std::end(prevDists), currentDist) != std::end(prevDists)) // wtf is here happening?
        {
            continue;
        }
        else
        {
            prevDists.push_back(currentDist);
        }

        std::list<Bunny>::iterator it = m_bunniesList.begin();
        std::advance(it, currentDist);  // increment it by rnd distance -- bad idea when list is huge
        if (it->isMutant() || it->getAge() < ADULT_AGE)
        {
            mutantsToCreate++;
        }
        else
        {
            it->convertToMutant();
            if (it->getAge() >= ADULT_AGE)
            {
                it->getSex() == "male" ? m_malesCtr-- : m_femalesCtr--;
            }
            m_mutantsCtr++;
        }
    }
}

bool Colony::isColonyTotallyInfected() const
{
    return m_mutantsCtr == getColonySize();
}

void Colony::performCull()
{
    throw std::logic_error("cull not implemented!");
}

size_t Colony::getColonySize() const
{
    return m_bunniesList.size();
}

size_t Colony::getMalesCtr() const
{
    return m_malesCtr;
}

size_t Colony::getFemalesCtr() const
{
    return m_femalesCtr;
}

size_t Colony::getKidsCtr() const
{
    return m_kidsCtr;
}

size_t Colony::getMutantsCtr() const
{
    return m_mutantsCtr;
}
