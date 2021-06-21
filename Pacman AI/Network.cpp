#include "Network.h"
#include "Neuron.h"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

typedef vector<Neuron> Layer;  //type Layer

//constructor
Network::Network(vector<unsigned> &topology)
{
    unsigned maxLayers = topology.size();  //the max num of layers

    //add new layers by looping
    for(unsigned layerNum = 0; layerNum < maxLayers; layerNum++)
    {
        //add a new layer
        NW_layers.push_back(Layer());
        unsigned numOutputs;  //for each neuron
        //if last layer, num of output of neuron is 0
        if(layerNum == topology.size() - 1)
            numOutputs = 0;
        //else num of output of neuron = num of neurons in next layer
        else
            numOutputs = topology[layerNum + 1];
        //add bias neuron to each layer
        for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++)
        {
            //create new neuron and add to layer at the last element
            NW_layers.back().push_back(Neuron(numOutputs, neuronNum));
        }
        //set value of 1 for bias neuron
        NW_layers.back().back().setOutputVal(0.01);
    }
}

//pass values to this layer's neurons to calculate
void Network::feedForward(vector<double> &inputVal)
{
    //check num of input = num of first layer neurons (without bias neuron)
    //if is false, abort & terminate program
    assert(inputVal.size() == NW_layers[0].size() - 1);

    //set values to first layer input neurons
    for(unsigned neuronNum = 0; neuronNum < inputVal.size(); neuronNum++)
        NW_layers[0][neuronNum].setOutputVal(inputVal[neuronNum]);
        //cout<< NW_layers[0][neuronNum].getOutputVal() <<"\t";

    //calculate this layer's neuron outputs
    for(unsigned layerNum = 1; layerNum < NW_layers.size(); layerNum++)
    {
        //cout<<endl<<layerNum <<endl;
        //set pointer to previous layer
        Layer &prevLayer = NW_layers[layerNum - 1];
        //pass previous layer's neuron output values
        for(unsigned n = 0; n < NW_layers[layerNum].size() - 1; n++)
            NW_layers[layerNum][n].calculateOutput(prevLayer);
    }
}

void Network::getResults(vector<double> &resultVal)
{
    resultVal.clear();  //clear all values in result vector
    //set values of last layer into result vector
    for(unsigned n = 0; n < NW_layers.back().size() - 1; n++)
    {
        resultVal.push_back(NW_layers.back()[n].getOutputVal());
    }
}
