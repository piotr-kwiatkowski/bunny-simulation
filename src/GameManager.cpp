#include "GameManager.h"
#include "Colony.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <memory>
#include <thread>

#define BORDER '#'
const int8_t GRID_WIDTH  = 80;
const int8_t GRID_HEIGHT = 40;

const int8_t LINE_MALE    = 2;
const int8_t LINE_FEMALE  = 4;
const int8_t LINE_KIDS    = 6;
const int8_t LINE_MUTANTS = 8;

static int16_t loop_ctr = 0;

int8_t GameManager::start()
{
    this->setWinSize(120, 50); // max reasonable height = 50
    this->drawGrid();
    this->drawLegend();

    Colony oColony; // TODO: use smart pointer
    if (!oColony.hasLoadedNames())
    {
        return EXIT_FAILURE;
    }

    oColony.populateColony();
    this->updateLegend(&oColony);

    //========================================================================
    //            MAIN GAME LOOP
    //========================================================================
    int16_t tmp_rescueCntr = 0;
    int16_t keyPressed = 0;
    while (true)
    {
        loop_ctr++;
        // iteration every 1 second
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (!this->nextYear(&oColony))
        {
            moveTo(30, GRID_HEIGHT / 2);
            std::cout << ">> GAME OVER <<";
            break;
        }

        if (++tmp_rescueCntr > 3)
        {
            std::cout << "-- max rescue counter approached!\n";
            return 66;
        }

        // press and hold SPACE to pause the game
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
    moveTo(0, GRID_HEIGHT + 4);
    std::cout << "loop_ctr: " << loop_ctr;
    return EXIT_SUCCESS;
}

bool GameManager::nextYear(Colony *a_oColony) const
{
    moveTo(loop_ctr, 0);
    std::cout << "-";
    a_oColony->incrementAge();
    a_oColony->killElders();
    a_oColony->infect();

    if (!a_oColony->breed())
    {
        moveTo(0, GRID_HEIGHT / 3);
        std::cout << "COLONY CAN NOT BREED!\n";
        return false;
    }

    // sort colony by age
    //a_oColony->m_bunniesList.sort([](Bunny a, Bunny b) { return a.getAge() > b.getAge(); });  // TODO: move it to method of Colony class
    this->updateLegend(a_oColony);
    
    /*
    moveTo(0, 10);
    std::cout
        << "-- is colony empty: " << std::boolalpha << a_oColony->isColonyEmpty() << std::noboolalpha
        << " -- colony totally infected: " << std::boolalpha << a_oColony->isColonyTotallyInfected() << std::noboolalpha << "\n";
    std::cout << "-- || : " << std::boolalpha << (a_oColony->isColonyEmpty() || a_oColony->isColonyTotallyInfected()) << std::noboolalpha << "\n";*/

    //return !(a_oColony->isColonyEmpty() || a_oColony->isColonyTotallyInfected());
    if (a_oColony->isColonyEmpty() || a_oColony->isColonyTotallyInfected())
    {
        return false;
    }
    return true;
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
    setColor(112);
    moveTo(0, 0);
    std::cout << std::setw(GRID_WIDTH) << std::setfill(BORDER) << "\n";
    for (int i = 1; i < GRID_HEIGHT; ++i)
    {
        moveTo(0, i);
        std::cout << BORDER;
        moveTo(GRID_WIDTH-2, i);
        std::cout << BORDER;
    }
    moveTo(0, GRID_HEIGHT);
    std::cout << std::setw(GRID_WIDTH) << std::setfill(BORDER) << "\n";
}

void GameManager::drawLegend() const
{
    moveTo(GRID_WIDTH + 2, LINE_MALE);
    std::cout << "MALES: ";
    moveTo(GRID_WIDTH + 2, LINE_FEMALE);
    std::cout << "FEMALES: ";
    moveTo(GRID_WIDTH + 2, LINE_KIDS);
    std::cout << "KIDS: ";
    moveTo(GRID_WIDTH + 2, LINE_MUTANTS);
    std::cout << "MUTANTS: ";
}

void GameManager::updateLegend(Colony *a_oColony) const
{
    moveTo(GRID_WIDTH + 15, LINE_MALE);
    std::cout << a_oColony->getMales();
    moveTo(GRID_WIDTH + 15, LINE_FEMALE);
    std::cout << a_oColony->getFemales();
    moveTo(GRID_WIDTH + 15, LINE_KIDS);
    std::cout << a_oColony->getKids();
    moveTo(GRID_WIDTH + 15, LINE_MUTANTS);
    std::cout << a_oColony->getMutants();
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
