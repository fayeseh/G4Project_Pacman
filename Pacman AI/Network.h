#ifndef NETWORK_H
#define NETWORK_H
#include <iostream>
#include <vector>
#include "Neuron.h"

using namespace std;

typedef vector<Neuron> Layer;  //type Layer

class Network
{
    public:
        //constructor
        Network(vector<unsigned> &topology);
        //pass values to neuron to calculate
        void feedForward(vector<double> &inputVal);
        //get last layer of output values
        void getResults(vector<double> &resultVal);

    private:
        vector<Layer> NW_layers;  //NW_layers[layerNum][neuronNum]
};

#endif // NETWORK_H
