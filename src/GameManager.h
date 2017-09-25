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

    void drawLegend() const;

    void updateLegend(Colony *a_oColony) const;

    // set game window size
    void setWinSize(int8_t a_x, int8_t a_y) const;

private:
    enum ConsoleColors // FIXME: use this to set colors in console
    {
        BLACK, DBLUE, DGREEN, DSEA, DRED,
        DVIOLET, DYELLOW, DWHITE, GREY, BLUE,
        GREEN, SEA, RED, PINK, YELLOW, WHITE
    };

    // move cursor to position [X, Y]
    void moveTo(int8_t a_x, int8_t a_y) const;

    // set color of console text
    void setColor(int a_color) const;

    // update colony (age, breeding, infecting etc.)
    bool nextYear(Colony *colony) const;

    // shortage to avoid using std::cout
    void print(std::string a_str) const; // TODO: argument as std::ostream?
};

