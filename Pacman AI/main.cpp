#include "Game.h"
#include "Network.h"

#include <thread>

using namespace std;

void createGame(CConsoleLoggerEx *Logger, Network *net, int &high) {
    //run pacman game
    Game* game = new Game(net, Logger);
    game->Go(high);
    delete game;
}

int main() {

    Network* nHolder[3];

    //initialize neural network
    unsigned numData = 10;
    unsigned numNeurons = 5;  //in hidden layers
    unsigned numOutput = 4;  //w,a,s,d

    vector<unsigned> topology;
    //first layer
    topology.push_back(numData);
    //hidden layers
    topology.push_back(numNeurons);
    //last layer
    topology.push_back(numOutput);

    for(int i = 0; i < 3; i++)
    {
        Network *testNet = new Network(topology);
        nHolder[i] = testNet;
    }

    int hHolder[3];  //for pass by reference high score

    CConsoleLoggerEx* cHolder[3];

    for(int i = 0; i < 3; i++) {
        CConsoleLoggerEx* cx = new CConsoleLoggerEx();
        cx->Create("PACMAN");
        cHolder[i] = cx;
    }

    thread t1(createGame, cHolder[0], nHolder[0], ref(hHolder[0]));
    thread t2(createGame, cHolder[1], nHolder[1], ref(hHolder[1]));
    thread t3(createGame, cHolder[2], nHolder[2], ref(hHolder[2]));

    t1.join();
    t2.join();
    t3.join();

    cout << "high score 1: " << hHolder[0] << endl;
    cout << "high score 2: " << hHolder[1] << endl;
    cout << "high score 3: " << hHolder[2] << endl;

    return 0;
}

//multithread
