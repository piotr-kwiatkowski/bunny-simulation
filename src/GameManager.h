#pragma once
#include <cstdint>
#include "Colony.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();

    int8_t startGame();
    bool GameManager::nextYear(Colony *colony) const;
};

