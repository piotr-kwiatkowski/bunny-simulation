#include "GameManager.h"
#include "Colony.h"
#include <iostream>
#include <windows.h>
#include <iomanip>

#define BORDER '#'
const int8_t GWIDTH  = 80;
const int8_t GHEIGHT = 40;

int8_t GameManager::startGame()
{
    Colony oColony;
    if (!oColony.hasLoadedNames())
    {
        return EXIT_FAILURE;
    }

    oColony.populateColony();
    oColony.print();

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
    moveTo(0, GHEIGHT + 1);
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
    a_oColony->m_colony.sort([](Bunny a, Bunny b) { return a.getAge() > b.getAge(); });  // TODO: move it to method of Colony class
    a_oColony->print();

    return a_oColony->m_colony.empty() || a_oColony->isColonyTotallyInfected();
}

void GameManager::print(std::string a_str) const
{
}

void GameManager::setWinSize(int8_t a_x, int8_t a_y) const
{
    COORD coord;
    coord.X = a_x;
    coord.Y = a_y;

    SMALL_RECT rect;
    rect.Top  = 0;
    rect.Left = 0;
    rect.Bottom = a_y - 1;
    rect.Right  = a_x - 1;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(handle, coord);  // set size of the internal buffer of the console
    SetConsoleWindowInfo(handle, TRUE, &rect);  // set window size
}

void GameManager::drawGrid() const
{
    setColor(14);
    moveTo(0, 0);
    std::cout << std::setw(GWIDTH) << std::setfill(BORDER) << "\n";
    for (int i = 1; i < GHEIGHT; ++i)
    {
        moveTo(0, i);
        std::cout << BORDER;
        moveTo(GWIDTH-2, i);
        std::cout << BORDER;
    }
    moveTo(0, GHEIGHT);
    std::cout << std::setw(GWIDTH) << std::setfill(BORDER) << "\n";
}

void GameManager::drawLegend() const
{
    moveTo(GWIDTH + 2, 2);
    std::cout << "MALES: ";
    moveTo(GWIDTH + 2, 4);
    std::cout << "FEMALES: ";
    moveTo(GWIDTH + 2, 6);
    std::cout << "KIDS: ";
    moveTo(GWIDTH + 2, 8);
    std::cout << "MUTANTS: ";
}

void GameManager::moveTo(int8_t a_x, int8_t a_y) const
{
    COORD coord; // FIXME: move this outside method?
    coord.X = a_x;
    coord.Y = a_y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameManager::setColor(int a_color) const
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a_color);
}
