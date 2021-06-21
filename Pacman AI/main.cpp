#include "Game.h"
#include "Network.h"

int main() {

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
    return 0;
}
