#include "GameManager.h"
#include "Colony.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <memory>
#include <thread>

#define BORDER '#'
const int8_t GRID_START = 0;

const int8_t GRID_WIDTH  = 79;
const int8_t GRID_HEIGHT = 41;

const int8_t LEGEND_INFO_WIDTH  = GRID_WIDTH + 3;
const int8_t LEGEND_VALUE_WIDTH = GRID_WIDTH + 15;

const int8_t LINE_YEAR    = 2;
const int8_t LINE_MALE    = 6;
const int8_t LINE_FEMALE  = 8;
const int8_t LINE_KIDS    = 10;
const int8_t LINE_MUTANTS = 12;

static int16_t yearCtr = 0;

int8_t GameManager::start()
{
    this->setWinSize(120, 50); // max reasonable height = 50
    system("color 07"); // FIXME
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
        yearCtr++;
        // iteration every 1 second
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (!this->performNextYear(&oColony))
        {
            moveTo(30, GRID_HEIGHT / 2);
            std::cout << ">> GAME OVER <<";
            break;
        }

        if (++tmp_rescueCntr > 30)
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
    std::cout << "loop_ctr: " << yearCtr;
    return EXIT_SUCCESS;
}

bool GameManager::performNextYear(Colony *a_oColony) const
{
    a_oColony->incrementAge();
    a_oColony->killElders();
    a_oColony->infect(); // TODO: first breeding? tests needed
    a_oColony->breed();

    // sort colony by age
    //a_oColony->m_bunniesList.sort([](Bunny a, Bunny b) { return a.getAge() > b.getAge(); });  // TODO: move it to method of Colony class
    this->updateLegend(a_oColony);
    
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
    //setColor(112);  // background: grey, text: black
    setColor(GREY);
    moveTo(1, 1);
    std::cout << std::setw(GRID_WIDTH) << std::setfill(BORDER) << "\n";
    for (int i = 2; i < GRID_HEIGHT; ++i)
    {
        moveTo(1, i);
        std::cout << BORDER;
        moveTo(GRID_WIDTH-1, i);
        std::cout << BORDER;
    }
    moveTo(1, GRID_HEIGHT);
    std::cout << std::setw(GRID_WIDTH) << std::setfill(BORDER) << "\n";
}

void GameManager::drawLegend() const
{
    moveTo(LEGEND_INFO_WIDTH, LINE_YEAR);
    std::cout << "YEAR: ";
    moveTo(LEGEND_INFO_WIDTH, LINE_MALE);
    std::cout << "MALES: ";
    moveTo(LEGEND_INFO_WIDTH, LINE_FEMALE);
    std::cout << "FEMALES: ";
    moveTo(LEGEND_INFO_WIDTH, LINE_KIDS);
    std::cout << "KIDS: ";
    moveTo(LEGEND_INFO_WIDTH, LINE_MUTANTS);
    std::cout << "MUTANTS: ";
}

void GameManager::updateLegend(Colony *a_oColony) const
{
    setColor(GREY);
    moveTo(LEGEND_VALUE_WIDTH, LINE_YEAR);
    std::cout << yearCtr;
    setColor(WHITE);
    moveTo(LEGEND_VALUE_WIDTH, LINE_MALE);
    std::cout << a_oColony->getMalesCtr();
    setColor(PINK);
    moveTo(LEGEND_VALUE_WIDTH, LINE_FEMALE);
    std::cout << a_oColony->getFemalesCtr();
    setColor(GREEN);
    moveTo(LEGEND_VALUE_WIDTH, LINE_KIDS);
    std::cout << a_oColony->getKidsCtr();
    setColor(RED);
    moveTo(LEGEND_VALUE_WIDTH, LINE_MUTANTS);
    std::cout << a_oColony->getMutantsCtr();
    setColor(GREY);
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
