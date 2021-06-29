#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cmath>
#include <Windows.h>
#include <algorithm>
#include <string>

#include "Constants.h"
#include "Game.h"
#include "Pacman.h"
#include "SetConsoleAttributes.h"
#include "ConsoleLogger.h"

using namespace std;

Pacman::Pacman(Game *const g)
: game(g) {
    hiScore = 0;
}

// check for user input every time the wait timer reaches 0
void Pacman::Move(CConsoleLoggerEx *Logger) {

    if (wait) {
        --wait;
    }
    else {
        GetDirection();
        if (TestForCollision() == false) {
            // replace old coordinates with a space
            SetCursorPosition(yOld, xOld);
            //cout << game->GetLevel(yOld, xOld);

            Logger->gotoxy(xOld, yOld+3);
            char LVL = game->GetLevel(yOld, xOld);
            char* lvl = &LVL;
            Logger->cprintf(lvl);

            // if the player picked up a pellet
            if (game->GetLevel(y, x) != ' ') {
                int scoreInc;
                if (game->GetLevel(y, x) == 'o') {
                    scoreInc = 50;
                    super = SUPER_MAX;
                }
                else {
                    scoreInc = 10;
                }
                PrintScore(scoreInc, Logger);
                game->SetLevel(y, x, ' ');
                --left;
            }
            Show(Logger);
            dirOld = dir;
            wait = PACMAN_MAX;
        }
    }
}

void Pacman::GetDirection() { //Where to implement the neural network
    dir = 'x';

    vector<double> inputValues;
    inputValues.push_back(GetX()/28.0);
    inputValues.push_back(GetY()/31.0);
    for(int i = 0; i < 4; ++i) {
        inputValues.push_back(game->ghosts[i]->GetX()/28.0);
        inputValues.push_back(game->ghosts[i]->GetY()/31.0);
    }
    game->neuralNet->feedForward(inputValues);
    ////cout<<inputValues.at(0);

    //get result from neural network
    vector<double> result; //store result from neural network in here
    game->neuralNet->getResults(result);


    int thismove = distance(
        result.begin(),
        max_element(result.begin(), result.end())
    );
    switch(thismove) {
        case 0:
            dir = 'w';
            break;
        case 1:
            dir = 'a';
            break;
        case 2:
            dir = 's';
            break;
        case 3:
            dir = 'd';
            break;
    }

}

bool Pacman::TestForCollision() {
    // save old coordinates
    xOld = x;
    yOld = y;
    // if the character in front of the player is a space, move in the appropriate direction
    switch (dir) {
    case 'a':
        // if travelling through the tunnel
        if (x == 0) {
            x = LEVEL_WIDTH - 1;
            icon = ICONS[1];
        }
        else if (strchr(NO_COLLISION_TILES, game->GetLevel(y, x - 1))) {
            --x;
            icon = ICONS[1];
        }
        break;
    case 'd':
        // if travelling through the tunnel
        if (x == LEVEL_WIDTH - 1) {
            x = 0;
            icon = ICONS[3];
        }
        else if (strchr(NO_COLLISION_TILES, game->GetLevel(y, x + 1))) {
            ++x;
            icon = ICONS[3];
        }
        break;
    case 'w':
        if (strchr(NO_COLLISION_TILES, game->GetLevel(y - 1, x))) {
            --y;
            icon = ICONS[0];
        }
        break;
    case 's':
        if (strchr(NO_COLLISION_TILES, game->GetLevel(y + 1, x))) {
            ++y;
            icon = ICONS[2];
        }
    }
    // if coordinates were not changed, there was a collision
    if (x == xOld && y == yOld) {
        return true;
    }
    return false;
}

void Pacman::PrintScore(int scoreInc, CConsoleLoggerEx *Logger) {
    // gain a life every time the score crosses a multiple of 10000
    if (score / 10000 < (score + scoreInc) / 10000) {
        ++lives;
        PrintLives(Logger);
    }
    score += scoreInc;
    SetTextColor(WHITE);
    SetCursorPosition(-2, 0);

    if (score == 0) {
        //cout << setw(7) << "00";
        Logger->gotoxy(3, 1);
        Logger->cprintf("00");
        //print highscore
        Logger->gotoxy(14, 1);
        Logger->cprintf("00");
    }
    else {
        //cout << setw(7) << score;
        Logger->gotoxy(3, 1);
        string SCO = to_string(score);
        char* sco = &SCO[0];
        Logger->cprintf(sco);
    }
    if (score > hiScore) {
        hiScore = score;
        //cout << setw(11) << hiScore;
        Logger->gotoxy(14, 1);
        string HISCO = to_string(hiScore);
        char* hisco = &HISCO[0];
        Logger->cprintf(hisco);
    }
}

void Pacman::PrintLives(CConsoleLoggerEx *Logger) {
    SetTextColor(color);
    SetCursorPosition(LEVEL_HEIGHT, 2);
    Logger->gotoxy(2, LEVEL_HEIGHT+3);
    for (int i = 1; i < lives; ++i) {
        //cout << ICONS[1] << " ";

        char Icon = ICONS[1];
        char* ic = &Icon;
        Logger->cprintf(color, ic);
        Logger->cprintf(" ");
    }
    //cout << " ";
    Logger->cprintf(" ");
}

void Pacman::PrintKillScore(CConsoleLoggerEx *Logger) {
    ++killCount;
    int scoreInc = 200 * (int)pow(2, killCount - 1);
    int length = (int)floor(log10(scoreInc)) + 1;
    int killX = x - 1;
    if (x == 0) {
        killX = x;
    }
    if (x > LEVEL_WIDTH - length) {
        killX = LEVEL_WIDTH - length;
    }
    SetTextColor(CYAN);
    SetCursorPosition(y, killX);
    //cout << scoreInc;

    Logger->gotoxy(killX, y+3);
    string SCI = to_string(scoreInc);
    char* scI = &SCI[0];
    Logger->cprintf(CYAN, scI);

    PrintScore(scoreInc, Logger);
    Sleep(750);
    SetCursorPosition(y, killX);
    Logger->gotoxy(killX, y+3);
    for (int i = killX; i < killX + length; ++i) {
        SetTextColor(DARK_BLUE);
        if (game->GetLevel(y, i) == char(250)) {
            SetTextColor(WHITE);
        }
        if (game->GetLevel(y, i) == 'o') {
            SetTextColor(game->GetPelletColor());
        }
        //cout << game->GetLevel(y, i);
        char LVL = game->GetLevel(y, i);
        char* lvl = &LVL;
        Logger->cprintf(lvl);
    }
    Show(Logger);
}

void Pacman::Dead(CConsoleLoggerEx *Logger) {
    Sleep(1000);
    game->HideAll();
    for (int i = 0; i < 8; ++i) {
        icon = ICONS[i % 4];
        Show(Logger);
        Sleep(100);
    }
    Hide(Logger);
    Sleep(500);
    --lives;
    if (lives != 0) {
        game->InitAll();
        game->ShowAll();
        PrintLives(Logger);
        game->PrintReady();
    }
    else {
        game->PrintGameOver();
    }
}

void Pacman::Show(CConsoleLoggerEx *Logger) {
    SetTextColor(color);
    SetCursorPosition(y, x);
    //cout << icon;

    Logger->gotoxy(x, y+3);
    char* ic = &icon;
    Logger->cprintf(color, ic);
}

void Pacman::Hide(CConsoleLoggerEx *Logger) {
    SetCursorPosition(y, x);
    //cout << game->GetLevel(y, x);

    Logger->gotoxy(x, y+3);
    char LVL = game->GetLevel(y, x);
    char* lvl = &LVL;
    Logger->cprintf(lvl);
}
