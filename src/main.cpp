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
        std::cout << "111";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        for (size_t i = 0; i < 10; i++)
        {
            pr.console("TOTAL: ", 60, 0);
        }
    }
}

class Log
{
    std::mutex m_mtx;
    std::ofstream f;
public:
    Log();

    void shared_print()
    {
        std::lock_guard<std::mutex> locker(m_mtx);
        f << "From Russia with love";
    }
};

void testFun(Log& log)
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
    /*GameManager oGM;
    oGM.start();*/

    Log lg;
    std::thread t1(testFun, lg);
    t1.join();
    //std::thread t2(print2);

    std::cin.ignore();

    return 0;
}