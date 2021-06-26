#include "Game.h"
#include "Network.h"
#include <Windows.h>
#include <iostream>
#include <thread>
#include "Game.h"
using namespace std;
void gamecycle(int iterations)
{
    int loop=0;
    while (loop< iterations)
    {
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
    Network testNet (topology);

    Game* game = new Game(&testNet);
    game->Go();
    delete game;
    loop ++;
    }

}
int main() {


    thread th1(gamecycle,1);
    thread th2(gamecycle,1);

    th1.join();
    th2.join();



    return 0;
}

//multithread
