#include <iostream>
#include <Windows.h>
#include <string>

#include "Constants.h"
#include "Game.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Pellet.h"
#include "SetConsoleAttributes.h"
#include "ConsoleLogger.h"

using namespace std;

Game::Game(Network *neural, CConsoleLoggerEx *Logger) {
    SetWindowTitle("PACMAN_AI");
    SetWindowSize(LEVEL_HEIGHT + 4, LEVEL_WIDTH);
    SetCursorVisibility(false);

    player = new Pacman(this);
    for (int i = 0; i < 4; ++i) {
        ghosts[i] = new Ghost(this);
        pellets[i] = new Pellet(this);
    }

    conLogger = Logger;  //pointer for CCloggerEx class
    neuralNet = neural;
}

Game::~Game() {
    delete player;
    for (int i = 0; i < 4; ++i) {
        delete ghosts[i];
        delete pellets[i];
    }
}

void Game::Go(int &high) {
    while (!gameEnd) {
        MainLoop(high);
    }
}

void Game::MainLoop(int &high) {

    player->SetScore(0); //begining score=0
    player->SetLives(1); //has 1 life
    bool gameOver = false;

    for (int levelNum = 1; levelNum <= 1; ++levelNum) {
        LoadLevel();
        // while there are still dots on the screen,

        while (player->GetLeft() != 0) {

            if (gameOver) {break;}

            player->Move(conLogger); // check for user input every time the wait timer reaches 0

            SetCursorPosition(-2, 24);
            conLogger->gotoxy(24, 1);
            SetTextColor(WHITE);

            if (CountDownTimer<100) {
                //cout << "0" << CountDownTimer;
                conLogger->gotoxy(25, 1);
                string CDT = to_string(CountDownTimer); //convert int to string
                char* cdt = &CDT[0];  //convert string to char*
                conLogger->cprintf(WHITE, cdt);
            }
            else {
                //cout << CountDownTimer; //to print the countdown timer
                string CDT = to_string(CountDownTimer); //convert int to string
                char* cdt = &CDT[0];
                conLogger->cprintf(WHITE, cdt);
            }

            if (CountDownTime()){ //if the countdowntime=0, the game ends
                gameOver=true;
                break;}

            if (!player->GetLives()) {
                gameOver = true;
                break;
            }

            MoveGhosts();
            CheckForDeath();
            if (!player->GetLives()) {
                gameOver = true;
                break;
            }
            UpdateTimers();
        }
        NextLevel();
    }
    high = player->hiScore;  //set high score from game
}

void Game::LoadLevel() {

    char levelMap[LEVEL_HEIGHT][LEVEL_WIDTH + 1] = {
        "1555555555555555555555555552",
        "6............^^............6",
        "6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
        "67^  ^.^   ^.^^.^   ^.^  ^86",
        "6.#%%$.#%%%$.#$.#%%%$.#%%$.6",
        "6..........................6",
        "6.!%%@.!@.!%%%%%%@.!@.!%%@.6",
        "6.#%%$.^^.#%%@!%%$.^^.#%%$.6",
        "6......^^....^^....^^......6",
        "355552.^#%%@ ^^ !%%$^.155554",
        "     6.^!%%$ #$ #%%@^.6     ",
        "     6.^^    B     ^^.6     ",
        "     6.^^ 155&&552 ^^.6     ",
        "555554.#$ 6      6 #$.355555",
        "      .   6I   C 6   .      ",
        "555552.!@ 6  P   6 !@.155555",
        "     6.^^ 35555554 ^^.6     ",
        "     6.^^          ^^.6     ",
        "     6.^^ !%%%%%%@ ^^.6     ",
        "155554.#$ #%%@!%%$ #$.355552",
        "6............^^............6",
        "6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
        "6.#%@^.#%%%$.#$.#%%%$.^!%$.6",
        "69..^^......X ........^^..06",
        "6%@.^^.!@.!%%%%%%@.!@.^^.!%6",
        "6%$.#$.^^.#%%@!%%$.^^.#$.#%6",
        "6......^^....^^....^^......6",
        "6.!%%%%$#%%@.^^.!%%$#%%%%@.6",
        "6.#%%%%%%%%$.#$.#%%%%%%%%$.6",
        "6..........................6",
        "3555555555555555555555555554"};

    char curChar;
    SetTextColor(WHITE);
    SetCursorPosition(-3, 3);
    conLogger->gotoxy(3, 0);
    //cout << "1UP";
    conLogger->cprintf(WHITE, "1UP");

    SetCursorPosition(-3, 9);
    conLogger->gotoxy(9, 0);
    //cout << "HIGH SCORE";
    conLogger->cprintf(WHITE, "HIGH SCORE");

    SetCursorPosition(-3, 21);
    conLogger->gotoxy(21, 0);
    //cout << "TIMER";
    conLogger->cprintf(WHITE, "TIMER");
    CountDownTimer = DOWN_MAX; //set the countdown time for 1 minute 15 seconds

    SetCursorPosition(-5, 21);
    conLogger->gotoxy(21, -2);
    player->PrintScore(0, conLogger);  //HOW TO SETTLE FOR OTHER CONSOLES
    SetCursorPosition(0, 0);
    conLogger->gotoxy(0, 3);
    player->SetLeft(0);

    for (int y = 0; y < LEVEL_HEIGHT; ++y) {
        for (int x = 0; x < LEVEL_WIDTH; ++x) {
            curChar = levelMap[y][x];
            //SetTextColor(DARK_BLUE);
            switch (curChar) {
            case 'X':
                player->SetYInit(y);
                player->SetXInit(x);
                level[y][x] = ' ';
                break;
            case 'B':
                ghosts[BLINKY]->SetYInit(y);
                ghosts[BLINKY]->SetXInit(x);
                ghosts[BLINKY]->SetColorInit(RED);
                ghosts[BLINKY]->SetDirOpp('s');
                level[y][x] = ' ';
                break;
            case 'P':
                ghosts[PINKY]->SetYInit(y);
                ghosts[PINKY]->SetXInit(x);
                ghosts[PINKY]->SetColorInit(MAGENTA);
                level[y][x] = ' ';
                break;
            case 'I':
                ghosts[INKY]->SetYInit(y);
                ghosts[INKY]->SetXInit(x);
                ghosts[INKY]->SetColorInit(CYAN);
                level[y][x] = ' ';
                break;
            case 'C':
                ghosts[CLYDE]->SetYInit(y);
                ghosts[CLYDE]->SetXInit(x);
                ghosts[CLYDE]->SetColorInit(YELLOW);
                level[y][x] = ' ';
                break;
            case '7': //pALLETS= 'O'
                pellets[0]->SetY(y);
                pellets[0]->SetX(x);
                SetTextColor(WHITE);
                level[y][x] = 'o';
                player->SetLeft(player->GetLeft() + 1);
                break;
            case '8':
                pellets[1]->SetY(y);
                pellets[1]->SetX(x);
                SetTextColor(WHITE);
                level[y][x] = 'o';
                player->SetLeft(player->GetLeft() + 1);
                break;
            case '9':
                pellets[2]->SetY(y);
                pellets[2]->SetX(x);
                SetTextColor(WHITE);
                level[y][x] = 'o';
                player->SetLeft(player->GetLeft() + 1);
                break;
            case '0':
                pellets[3]->SetY(y);
                pellets[3]->SetX(x);
                SetTextColor(WHITE);
                level[y][x] = 'o';
                player->SetLeft(player->GetLeft() + 1);
                break;
            case '.':
                SetTextColor(WHITE);
                level[y][x] = char(250); //char 250 is a small square symbol
                player->SetLeft(player->GetLeft() + 1);
                break;
            case ' ':
                level[y][x] = curChar;
                break;
            case '&':
                SetTextColor(WHITE);
                curChar = '%';
            }
            if (curChar == '1') {  //wall symbol
                level[y][x] = char(201);
            }
            else if (curChar == '2') {  //wall symbol
                level[y][x] = char(187);
            }
            else if (curChar == '3') {  //wall symbol
                level[y][x] = char(200);
            }
            else if (curChar == '4') {  //wall symbol
                level[y][x] = char(188);
            }
            else if (curChar == '5') {  //wall symbol
                level[y][x] = char(205);
            }
            else if (curChar == '6') {  //wall symbol
                level[y][x] = char(186);
            }
            else if (curChar == '!') {  //wall symbol
                level[y][x] = char(218);
            }
            else if (curChar == '@') {  //wall symbol
                level[y][x] = char(191);
            }
            else if (curChar == '#') {
                level[y][x] = char(192);
            }
            else if (curChar == '$') {
                level[y][x] = char(217);
            }
            else if (curChar == '%') {
                level[y][x] = char(196);
            }
            else if (curChar == '^') {
                level[y][x] = char(179);
            }
            //cout << level[y][x];
            char* lvl = &level[y][x];
            conLogger->cprintf(lvl);
        }
        SetCursorPosition(y + 1, 0);
        int baseCursor = 3;  //y+3
        conLogger->gotoxy(0, baseCursor+y+1);
    }
    InitAll();
    ShowAll();
    player->PrintLives(conLogger);
    PrintReady();
}

void Game::NextLevel() {
    Sleep(1000);
    HideAll();
    SetCursorPosition(12, 13);
    conLogger->gotoxy(13, 15);
    //cout << "  ";
    conLogger->cprintf(" ");
    for (int i = 0; i < 4; ++i) {
        //SetScreenColor(WHITE);
        player->Show(conLogger);
        Sleep(200);
        //SetScreenColor(DARK_BLUE);
        player->Show(conLogger);
        Sleep(200);
    }
    SetCursorPosition(0, 0);
    conLogger->gotoxy(0, 3);
    InitAll();
}

void Game::PrintReady() {
    //SetTextColor(YELLOW);
    SetCursorPosition(17, 11);
    conLogger->gotoxy(11, 20);
    //cout << "READY!";
    conLogger->cprintf(YELLOW, "READY!");
    Sleep(2000);
    SetCursorPosition(17, 11);
    conLogger->gotoxy(11, 20);
    //cout << "      ";
    conLogger->cprintf("      ");
}

void Game::PrintGameOver() {
    SetCursorPosition(17, 9);
    conLogger->gotoxy(9, 20);
    //SetTextColor(RED);
    //cout << "GAME  OVER";
    conLogger->cprintf(RED, "GAME  OVER");
    Sleep(1000);
    gameEnd = true;  //go() while loop ends
}

void Game::MoveGhosts() {
    // check for ghost mode changes
    if (player->GetSuper() == SUPER_MAX) {
        player->SetKillCount(0);
        for (int i = 0; i < 4; ++i) {
            if (ghosts[i]->GetMode() != 'd') {
                ghosts[i]->SetColor(BLUE);
            }
            if (ghosts[i]->GetMode() == 's' || ghosts[i]->GetMode() == 'c') {
                ghosts[i]->SetMode('r');
            }
        }
        ShowAll();
    }
    if (player->GetLeft() == 235 && ghosts[PINKY]->GetMode() == 'w') {
        ghosts[PINKY]->SetMode('e');
    }
    if (player->GetLeft() == 200 && ghosts[INKY]->GetMode() == 'w') {
        ghosts[INKY]->SetMode('e');
    }
    if (player->GetLeft() == 165 && ghosts[CLYDE]->GetMode() == 'w') {
        ghosts[CLYDE]->SetMode('e');
    }
    for (int i = 0; i < 4; ++i) {
        ghosts[i]->Move(player->GetY(), player->GetX(), conLogger);
    }
    ShowAll();
}

void Game::UpdateTimers() {
    // handle super pacman
    if (player->GetSuper()) {
        player->SetSuper(player->GetSuper() - 1);
        if (player->GetSuper() <= 112 && player->GetSuper() % 28 == 0) {
            for (int i = 0; i < 4; ++i)
            if (ghosts[i]->GetColor() == BLUE) {
                ghosts[i]->SetColor(WHITE);
            }
            ShowAll();
        }
        if (player->GetSuper() <= 98 && (player->GetSuper() + 14) % 28 == 0) {
            for (int i = 0; i < 4; ++i) {
                if (ghosts[i]->GetColor() == WHITE && ghosts[i]->GetMode() != 'd' && ghosts[i]->GetMode() != 'n') {
                    ghosts[i]->SetColor(BLUE);
                }
            }
            ShowAll();
        }
        if (!player->GetSuper()) {
            for (int i = 0; i < 4; ++i) {
                if (ghosts[i]->GetMode() != 'd' && ghosts[i]->GetMode() != 'n') {
                    ghosts[i]->SetColor(ghosts[i]->GetColorInit());
                }
                if (ghosts[i]->GetMode() == 'r') {
                    ghosts[i]->SetModeOld(ghosts[i]->GetMode());
                    ghosts[i]->SetMode('c');
                }
            }
            ShowAll();
        }
    }
    // handle flashing 1UP
    if (oneUpTimer) {
        --oneUpTimer;
    }
    else {
        if (oneUpColor == WHITE) {
            oneUpColor = BLACK;
        }
        else {
            oneUpColor = WHITE;
        }
        //SetTextColor(oneUpColor);
        SetCursorPosition(-3, 3);
        conLogger->gotoxy(3, 0);
        //cout << "1UP";
        conLogger->cprintf("1UP");
        oneUpTimer = ONE_UP_MAX;
    }
    // handle flashing super pellets
    if (pelletTimer) {
        --pelletTimer;
    }
    else {
        if (pelletColor == WHITE) {
            pelletColor = BLACK;
        }
        else {
            pelletColor = WHITE;
        }
        //SetTextColor(pelletColor);
        for (int i = 0; i < 4; ++i) {
            pellets[i]->Print(conLogger);
        }
        ShowAll();
        pelletTimer = PELLET_MAX;
    }

    // handle ghost chase/scatter mode
    if (ghostModeTimer) {
        --ghostModeTimer;
        if (ghostModeTimer == MODE_MAX / 4) {
            for (int i = 0; i < 4; ++i) {
                if (ghosts[i]->GetMode() == 'c') {
                    ghosts[i]->SetMode('s');
                }
            }
        }
    }
    else {
        for (int i = 0; i < 4; ++i) {
            if (ghosts[i]->GetMode() == 's') {
                ghosts[i]->SetMode('c');
            }
        }
        ghostModeTimer = MODE_MAX;
    }

    Sleep(15);
}

void Game::CheckForDeath() {

    for (int i = 0; i < 4; ++i) {
        if (player->GetX() == ghosts[i]->GetX() && player->GetY() == ghosts[i]->GetY() &&
            ghosts[i]->GetMode() != 'd' && ghosts[i]->GetMode() != 'n') {
            if (ghosts[i]->GetMode() != 'r') {
                player->Dead(conLogger);
            }
            else {
                player->PrintKillScore(conLogger);
                ghosts[i]->Dead();
            }
        }
    }
}

//additional countdown time feature
bool Game::CountDownTime(){

    CountDownTimer--;
    if(CountDownTimer<0) {
        return true;
    }
    else
        return false;
}

void Game::ShowAll(){
    player->Show(conLogger);
    for (int i = 0; i < 4; ++i) {
        ghosts[i]->Show(conLogger);
    }
}

void Game::HideAll() {
    player->Hide(conLogger);
    for (int i = 0; i < 4; ++i) {
        ghosts[i]->Hide(conLogger);
    }
}

void Game::InitAll() {
    player->SetY(player->GetYInit());
    player->SetX(player->GetXInit());
    player->SetColor(YELLOW);
    player->SetIcon(ICONS[1]);
    player->SetDirOld('a');
    player->SetWait(0);
    player->SetSuper(0);
    for (int i = 0; i < 4; ++i) {
        ghosts[i]->SetY(ghosts[i]->GetYInit());
        ghosts[i]->SetX(ghosts[i]->GetXInit());
        ghosts[i]->SetColor(ghosts[i]->GetColorInit());
        ghosts[i]->SetMode('w');
        ghosts[i]->SetWait(0);
        ghosts[i]->SetIcon(GHOST_ICON);
    }
    ghosts[BLINKY]->SetMode('c');
    ghosts[BLINKY]->SetModeOld('c');
    if (player->GetLeft() <= 235) {
        ghosts[PINKY]->SetMode('e');
    }
    if (player->GetLeft() <= 200) {
        ghosts[INKY]->SetMode('e');
    }
    if (player->GetLeft() <= 165) {
        ghosts[CLYDE]->SetMode('e');
    }
}
