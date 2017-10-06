#pragma once

#include <mutex>

// console print wrapper
class Print
{
public:
    void console(std::string a_msg, size_t a_x, size_t a_y);

private:
    std::mutex mtx;
    //std::ofstream f;

    void moveTo(size_t a_x, size_t a_y);
};

