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

    Colony bunColony;

    std::list<Bunny> bunniesColony;
    oColony.populateColony(&bunniesColony);
    oColony.printColony(&bunniesColony);

    //========================================================================
    //            MAIN GAME LOOP
    //========================================================================
    int16_t rescueCntr = 0;
    int16_t res = 0;
    while (true)
    {
        // iteration every 1 second
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (!oColony.nextYear(&bunniesColony))
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
            res = GetAsyncKeyState(VK_SPACE);
            if (((0x80000000 & res) != 0) || ((0x00000001 & res) != 0))
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