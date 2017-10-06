/*
    =======================
         2017 UPDATE 
    =======================
 */

#include <iostream>
#include <Windows.h>
#include <ostream>

#include <thread>
#include <mutex>

#include "GameManager.h"

// tmp function to display console colors
void clrs()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // you can loop k higher to see more color choices
    for (int k = 1; k < 255; k++)
    {
        // pick the colorattribute k you want
        SetConsoleTextAttribute(hConsole, k);
        std::cout << k << " Sample text\n";
    }
}

int main(int argc, char const *argv[])
{
    GameManager oGM;
    oGM.start();

    std::cout << "\nPress enter to close program...";
    std::cin.ignore();

    return 0;
}