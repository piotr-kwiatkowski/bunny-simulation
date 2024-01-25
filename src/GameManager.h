#pragma once
#include <cstdint>
#include "Colony.h"

class GameManager
{
public:
    // main game loop
    int8_t start();

    // draw template grid for game
    void drawGrid() const;

    void printGameInfo() const;

    void updateGameInfo(Colony *a_oColony) const;

    // set game window size
    void setWinSize(int8_t a_x, int8_t a_y) const;

    // FIXME: should be private?
    // move cursor to position [X, Y]
    void moveCursorTo(int8_t a_x, int8_t a_y) const;

private:
    enum ConsoleColors
    {
        BLACK, DARK_BLUE, DARK_GREEN, DARK_SEA, DARK_RED,
        DARK_VIOLET, DARK_YELLOW, DARK_WHITE, GREY, BLUE,
        GREEN, SEA, RED, PINK, YELLOW, WHITE
    };

    // set color of console text
    void setColor(ConsoleColors a_color) const;

    // update colony (age, breeding, infecting etc.)
    bool performNextYear(Colony *a_oColony) const;

    // shortage to avoid using std::cout
    void print(std::string a_str) const; // TODO: argument as std::ostream?
};

