#include "Neuron.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<Neuron> Layer;

//constructor
Neuron::Neuron(unsigned numOutputs, unsigned index)
{
    for(unsigned i = 0; i < numOutputs; i++)
    {
        //add random weights to each neuron weights
        N_weights.push_back(randomWeight());
    }
    //set index of neuron
    N_index = index;
}

//function to calculate input with weights
void Neuron::calculateOutput(Layer &prevLayer)
{
    double sum = 0.0;
    //all previous layer neuron's output * weight
    //add above result into sum
    for(unsigned n = 0; n < prevLayer.size(); n++)
        sum += prevLayer[n].getOutputVal() * prevLayer[n].N_weights[N_index];
    //call transfer function to modify the total sum
    //set modified sum into output of neuron
    N_outputVal = Neuron::transferFunction(sum);
}

//private function to return random values for weights
double Neuron::randomWeight(void)
{
    return rand() / double(RAND_MAX);  //in decimals
}

//private function to return value in between -1 & 1
double Neuron::transferFunction(double x)
{
    return tanh(x);
}
