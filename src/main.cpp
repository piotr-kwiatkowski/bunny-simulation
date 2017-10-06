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


// console print wrapper
class Print
{
    std::mutex mtx;

public:
    Print(std::string a_msg, size_t a_x, size_t a_y)
    {

    }

};


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