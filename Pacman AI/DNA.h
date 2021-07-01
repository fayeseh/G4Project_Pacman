#ifndef DNA_H
#define DNA_H

#include "Network.h"
#include <iostream>
#include <vector>

using namespace std;

class DNA
{
    public:
        DNA(vector<unsigned> &topo);
        //vector<unsigned> topology;
        double fitness;
        Network* neuralNetwork;

        //function to get network from weights
        Network* weightsToNetwork(vector<double> weights, vector<unsigned>topology);
        //function to get weights from network
        vector<double> networkToWeights(Network* net);

};

#endif // DNA_H
