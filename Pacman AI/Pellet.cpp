#include <iostream>

#include "Game.h"
#include "Pellet.h"
#include "SetConsoleAttributes.h"
#include "ConsoleLogger.h"

using namespace std;

Pellet::Pellet(Game *const g)
: game(g) {}

void Pellet::Print(CConsoleLoggerEx *Logger) {
    SetCursorPosition(y, x);
    //cout << game->GetLevel(y, x);

    Logger->gotoxy(x, y+3);
    char LVL = game->GetLevel(y, x);
    char* lvl = &LVL;
    Logger->cprintf(lvl);
}
