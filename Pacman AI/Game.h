#ifndef GAME_H
#define GAME_H

#include "Constants.h"
#include "Network.h"
#include "Game.h"
#include "Ghost.h"


class Pacman;

class Pellet;

class Game {
private:
    char level[LEVEL_HEIGHT][LEVEL_WIDTH];
    int oneUpTimer = ONE_UP_MAX;
    int oneUpColor = WHITE;
    int pelletTimer = PELLET_MAX;
    int pelletColor = WHITE;
    int ghostModeTimer = MODE_MAX;
    int CountDownTimer = DOWN_MAX;



    void MainLoop();




public:
    Game(Network* neural);
    ~Game();
    void Go();

    void LoadLevel();
    void NextLevel();
    void PrintReady();
    void PrintGameOver();

    void MoveGhosts();
    void UpdateTimers();
    void CheckForDeath();
    void ShowAll();
    void HideAll();
    void InitAll();
    bool CountDownTime();

    char GetLevel(int y, int x) { return level[y][x];    }
    int GetOneUpTimer()         { return oneUpTimer;     }
    int GetOneUpColor()         { return oneUpColor;     }
    int GetPelletTimer()        { return pelletTimer;    }
    int GetPelletColor()        { return pelletColor;    }
    int GetGhostModeTimer()     { return ghostModeTimer; }
    int GetCountDownTimer()     { return CountDownTimer; }

    void SetLevel(int y, int x, char c) { level[y][x] = c;    }
    void SetOneUpTimer(int t)           { oneUpTimer = t;     }
    void SetOneUpColor(int c)           { oneUpColor = c;     }
    void SetPelletTimer(int t)          { pelletTimer = t;    }
    void SetPelletColor(int c)          { pelletColor = c;    }
    void SetGhostModeTimer(int t)       { ghostModeTimer = t; }
    void SetCountDownTimer(int t)       { CountDownTimer = t; }

    //NeuralNetwork things
    Network* neuralNet;

    Pacman* player;
    Ghost* ghosts[4];
    Pellet* pellets[4];
};

#endif
