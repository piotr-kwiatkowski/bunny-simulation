#include "GameManager.h"
#include "Colony.h"
#include <iostream>
#include <windows.h>


GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

int8_t GameManager::startGame()
{
    Colony oColony;
    if (!oColony.hasLoadedNames())
    {
        return EXIT_FAILURE;
    }

    oColony.populateColony();
    oColony.printColony();

    //========================================================================
    //            MAIN GAME LOOP
    //========================================================================
    int16_t rescueCntr = 0;
    int16_t keyPressed = 0;
    while (true)
    {
        // iteration every 1 second
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (!this->nextYear(&oColony))
        {
            break;
        }

        if (++rescueCntr > 100)
        {
            std::cout << "-- max rescue counter approached!\n";
            return 66;
        }

        while (true)
        {
            keyPressed = GetAsyncKeyState(VK_SPACE);
            if (((0x80000000 & keyPressed) != 0) || ((0x00000001 & keyPressed) != 0))
            {
                continue;
            }
            else
            {
                break;
            }
        }
    }
    //========================================================================
    return EXIT_SUCCESS;
}

bool GameManager::nextYear(Colony *a_oColony) const
{
    a_oColony->incrementColonyAge();
    a_oColony->killElders();
    //a_oColony->infect();

    if (!a_oColony->breed())
    {
        std::cout << "COLONY CAN NOT BREED!\n";
        return false;
    }

    // sort colony by age
    a_oColony->m_colony.sort([](Bunny a, Bunny b) { return a.getAge() > b.getAge(); });  // TODO: move it to function
    a_oColony->printColony();

    return a_oColony->m_colony.empty() || a_oColony->isColonyTotallyInfected();
}