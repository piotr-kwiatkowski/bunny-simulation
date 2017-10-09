/*
    ====================================
         Author:    Piotr Kwiatkowski
         Created:   2017
    ====================================
 */

#include <iostream>
#include <Windows.h>
#include <ostream>

#include <thread>
#include <mutex>

#include "GameManager.h"
#include "Print.h"

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

void print1()
{
    Print pr;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        for (size_t i = 0; i < 10; i++)
        {
            pr.console("TOTAL: ", 60, 0);
        }
    }
}

void print2()
{
    int i = 0;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1200));
        std::cout << "\nprint2: " << i++ << "\n";
    }
}

int main(int argc, char const *argv[])
{
    GameManager oGM;
    oGM.start();

    /*Print pr;
    std::thread t1(print1);
    std::thread t2(print2);
    t1.detach();
    t2.detach();*/

    //std::cout << "\nPress enter to close program...";
    std::cin.ignore();

    return 0;
}