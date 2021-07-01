#ifndef PELLET_H
#define PELLET_H

#include "ConsoleLogger.h"

class Game;

class Pellet {
private:
    int y, x;

    Game *game;

public:
    Pellet(Game *const g);
    void Print(CConsoleLoggerEx *Logger);

    void SetY(int y) { this->y = y; }
    void SetX(int x) { this->x = x; }
};

#endif
