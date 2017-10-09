#include "Print.h"
#include <Windows.h>
#include <iostream>
#include <string>


void Print::console(std::string a_msg, size_t a_x, size_t a_y)
{
    std::lock_guard<std::mutex> guard(mtx);
    moveTo(a_x, a_y);
    std::cout << a_msg;
    f << "test";
}

void Print::moveTo(size_t a_x, size_t a_y)
{
    COORD coord; // FIXME: move this outside method?
    coord.X = a_x;
    coord.Y = a_y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
