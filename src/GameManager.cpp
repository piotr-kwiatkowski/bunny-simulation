#include "GameManager.h"
#include "Colony.h"
#include "Print.h"

#include <iostream>
#include <windows.h>
#include <iomanip>
#include <memory>
#include <thread>
#include <random>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "../inc/al.h"
#include "../inc/alc.h"

constexpr auto BORDER = '#';

// FIXME: should these be members of the GameManager class?
const size_t WINDOW_WIDTH  = 125;
const size_t WINDOW_HEIGHT = 58; // max reasonable height for ASUS == 50

const size_t GRID_START = 0;

const size_t GRID_WIDTH  = 98;
const size_t GRID_HEIGHT = 51;

const size_t MAX_BUNNIES = GRID_WIDTH * GRID_HEIGHT; // TODO: use it to verify if there is more bunnies than places within grid

const size_t LEGEND_INFO_WIDTH  = GRID_WIDTH + 3;
const size_t LEGEND_VALUE_WIDTH = GRID_WIDTH + 15;

const size_t LINE_YEAR    = 2;
const size_t LINE_MALE    = 6;
const size_t LINE_FEMALE  = 8;
const size_t LINE_KIDS    = 10;
const size_t LINE_MUTANTS = 12;

static size_t yearCtr = 0;
static bool gameOver = false;

static void printTest()
{
    size_t i = 0;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        COORD coord; // FIXME: move this outside method?
        coord.X = WINDOW_WIDTH - 2;
        coord.Y = WINDOW_HEIGHT - 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << i;
        i > 8 ? i = 0 : i++;
        if (gameOver)
        {
            break;
        }
    }
}

int8_t GameManager::start()
{
    //PlaySoundA("snd/wind.wav", NULL, SND_ASYNC | SND_LOOP); // FIXME
    setWinSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    system("color 07"); // FIXME: what does this do?
    drawGrid();
    printGameInfo();
    //return EXIT_SUCCESS;
    
    Colony oColony;
    if (!oColony.hasLoadedNames()) // TODO: verify
    {
        return EXIT_FAILURE;
    }

    oColony.initColony(); // TODO: verify
    updateGameInfo(&oColony);   // TODO: verify

    // debug:
    /*for (size_t i = 0; i < 5; i++)
    {
        performNextYear(&oColony);
        std::cin.ignore();
    }
    return EXIT_SUCCESS;*/


    //========================================================================
    //            MAIN GAME LOOP
    //========================================================================
    //int16_t keyPressed = 0;
    
    //std::thread test_thread(printTest);

    //Print pr;
    // thread 1 for calculations (original Colony object)
    // infinite loop until game over approached --> gameOver = true;
    //std::thread thread_math();

    // thread 2 for drawing (copied Colony object?)
    // draw until gameOver == true
    //std::thread thread_draw(std::ref(pr));

    // thread 1 join
    //thread_math.join();

    // thread 2 join
    //thread_draw.join();

    // loop to remove?
    while (true)
    {
        yearCtr++;
        // iteration every 1 second
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (!performNextYear(&oColony))
        {
            gameOver = true;
            moveCursorTo(25, (GRID_HEIGHT / 2)-1); // FIXME: magic numbers
            std::cout << std::setw(20) << "COLONY TOTALLY INFECTED";
            moveCursorTo(25, GRID_HEIGHT / 2); // FIXME: magic numbers
            std::cout << std::setw(20) << ">> GAME OVER <<";

            // DEBUGGING:
            moveCursorTo(10, GRID_HEIGHT + 5);
            std::cout << std::setw(20) << "tenis";

            break;
        }
        
        // press and hold SPACE to pause the game
        //while (true)
        //{
        //    keyPressed = GetAsyncKeyState(VK_SPACE);
        //    if (((0x80000000 & keyPressed) != 0) || ((0x00000001 & keyPressed) != 0))
        //    {
        //        continue;
        //    }
        //    else
        //    {
        //        break;
        //    }
        //}
    }
    //========================================================================
    moveCursorTo(0, GRID_HEIGHT + 4);
    
    //test_thread.join();
    
    return EXIT_SUCCESS;
}

bool GameManager::performNextYear(Colony *a_oColony) const
{
    a_oColony->incrementAge();
    a_oColony->killElders();
    a_oColony->breed();
    a_oColony->infect();     // TODO: breeding should be first?

    // TODO: food shortage if colony has 1000 bunnies
    /*if (a_oColony->getColonySize() >= 1000)
    {
         a_oColony->performDeathByStarvation();
    }*/

    // sort colony by age
    //a_oColony->m_bunniesList.sort([](Bunny a, Bunny b) { return a.getAge() > b.getAge(); });  // TODO: move it to method of Colony class
    updateGameInfo(a_oColony);
    
    return !(a_oColony->isColonyEmpty() || a_oColony->isColonyTotallyInfected());
}

void GameManager::print(std::string a_str) const // FIXME: naming; print what?
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

    // FOR DEBUGGING:
    /*setColor(WHITE);
    for (int i = 1; i < GRID_WIDTH; ++i)
    {
        moveCursorTo(i, 0);
        if (i % 10 == 1)
        {
            std::cout << i % 10;
        }
    }*/

    setColor(GREY);
    moveCursorTo(1, 1);
    std::cout << std::setw(GRID_WIDTH) << std::setfill(BORDER) << "\n";
    for (int i = 2; i < GRID_HEIGHT; ++i)
    {
        moveCursorTo(1, i);
        std::cout << BORDER;
        moveCursorTo(GRID_WIDTH-1, i);
        std::cout << BORDER;
    }
    moveCursorTo(1, GRID_HEIGHT);
    std::cout << std::setw(GRID_WIDTH) << std::setfill(BORDER) << "\n"
        << std::setfill(' ');
}

void GameManager::printGameInfo() const
{
    moveCursorTo(LEGEND_INFO_WIDTH, LINE_YEAR);
    std::cout << "YEAR: ";
    moveCursorTo(LEGEND_INFO_WIDTH, LINE_MALE);
    std::cout << "MALES: ";
    moveCursorTo(LEGEND_INFO_WIDTH, LINE_FEMALE);
    std::cout << "FEMALES: ";
    moveCursorTo(LEGEND_INFO_WIDTH, LINE_KIDS);
    std::cout << "KIDS: ";
    moveCursorTo(LEGEND_INFO_WIDTH, LINE_MUTANTS);
    std::cout << "MUTANTS: ";
}

void GameManager::updateGameInfo(Colony *a_oColony) const
{
    setColor(GREY);
    moveCursorTo(LEGEND_VALUE_WIDTH, LINE_YEAR);
    printf("%3zu", yearCtr);
    //PlaySoundA(TEXT("snd/01.wav"), NULL, SND_ASYNC);
    setColor(WHITE);
    moveCursorTo(LEGEND_VALUE_WIDTH, LINE_MALE);
    printf("%3zu", a_oColony->getMalesCtr());
    setColor(PINK);
    moveCursorTo(LEGEND_VALUE_WIDTH, LINE_FEMALE);
    printf("%3zu", a_oColony->getFemalesCtr());
    setColor(GREEN);
    moveCursorTo(LEGEND_VALUE_WIDTH, LINE_KIDS);
    printf("%3zu", a_oColony->getKidsCtr());
    setColor(RED);
    moveCursorTo(LEGEND_VALUE_WIDTH, LINE_MUTANTS);
    printf("%3zu", a_oColony->getMutantsCtr());
    setColor(GREY);
}

// TODO: erase after method completion in Print class
void GameManager::moveCursorTo(int8_t a_x, int8_t a_y) const
{
    COORD coord; // FIXME: move this outside method?
    coord.X = a_x;
    coord.Y = a_y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameManager::setColor(ConsoleColors a_color) const
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a_color);
}
