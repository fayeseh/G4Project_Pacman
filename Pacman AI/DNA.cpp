#include <iostream>
#include <vector>

#include "DNA.h"
#include "Network.h"
#include "Neuron.h"

using namespace std;

DNA::DNA(vector<unsigned> &topo)
{
    neuralNetwork = new Network(topo);
}

//function to get network from weights
Network* DNA::weightsToNetwork(vector<double> weights, vector<unsigned>topology)
{
    int i = 0;
    Network* net = new Network(topology);
    vector<Layer> tempNetwork;
    for(unsigned layerNum = 0; layerNum < net->NW_layers.size(); layerNum++)
    {
        //cout<<"Layer " <<layerNum <<endl;
        Layer tempLayer;
        for(unsigned neuronNum = 0; neuronNum < net->NW_layers.at(layerNum).size(); neuronNum++)
        {
            //cout<<"Neuron " <<neuronNum <<endl;
            Neuron tempNeuron(net->NW_layers.at(layerNum).at(neuronNum).N_weights.size(), neuronNum);
            vector<double> tempWeights;
            for(unsigned weightNum = 0; weightNum < net->NW_layers.at(layerNum).at(neuronNum).N_weights.size(); weightNum++ )
            {
                //cout<<"Weight " <<weightNum <<endl;
                tempWeights.push_back(weights[i]);
                i++;
            }
            tempNeuron.N_weights = tempWeights;
            tempLayer.push_back(tempNeuron);
        }
        tempNetwork.push_back(tempLayer);
    }
    net->NW_layers = tempNetwork;
    return net;

}

//function to get weights from network
vector<double> DNA::networkToWeights(Network* net)
{
    vector<double> temp;
    for(unsigned layerNum = 0; layerNum < net->NW_layers.size(); layerNum++)
    {
        //cout<<net->NW_layers.size() <<endl;
        //cout<<"Layer " <<layerNum <<endl;
        for(unsigned neuronNum = 0; neuronNum < net->NW_layers.at(layerNum).size(); neuronNum++)
        {
            //cout<<net->NW_layers.at(layerNum).size() <<endl;
            //cout<<"Neuron " <<neuronNum <<endl;
            for(unsigned weightNum = 0; weightNum < net->NW_layers.at(layerNum).at(neuronNum).N_weights.size(); weightNum++ )
            {
                //cout<<net->NW_layers.at(layerNum).at(neuronNum).N_weights.size() <<endl;
                //cout<<"Weight " <<weightNum <<endl;
                temp.push_back(net->NW_layers.at(layerNum).at(neuronNum).N_weights.at(weightNum));
            }
        }
    }
    //cout<<"Returned" <<endl;
    return temp;
}
