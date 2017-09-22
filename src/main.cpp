/*
    ============================================
         2017 UPDATE for Graduation project   
    ============================================
 */

#include <iostream>
#include "GameManager.h"

int main(int argc, char const *argv[])
{
    std::cout << "This is a test of a new branch\n";

    GameManager oGM;
    oGM.setWinSize(127, 64);
    oGM.drawGrid();
    //oGM.startGame();

    //std::cout << "\nPress enter to close program...";
    //std::cin.ignore();

    return 0;
}