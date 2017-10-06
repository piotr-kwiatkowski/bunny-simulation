#include "Print.h"
#include <Windows.h>


void Print::console(std::string a_msg, size_t a_x, size_t a_y)
{
    moveTo(a_x, a_y);


}

void Print::moveTo(size_t a_x, size_t a_y)
{
    COORD coord; // FIXME: move this outside method?
    coord.X = a_x;
    coord.Y = a_y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
