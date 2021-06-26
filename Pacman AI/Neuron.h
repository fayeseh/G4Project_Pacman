#ifndef NEURON_H
#define NEURON_H
#include <iostream>
#include <vector>

using namespace std;

class Neuron;
typedef vector<Neuron> Layer;  //type Layer

class Neuron
{
    public:
        //constructor
        Neuron(unsigned numOutputs, unsigned index);
        //set value of neuron output
        void setOutputVal(double v) {N_outputVal = v;}
        //get value of neuron output
        double getOutputVal(void) {return N_outputVal;}
        //calculate input with weights
        void calculateOutput(Layer &prevLayer);


    private:
        double N_outputVal;  //neuron's output value
        unsigned N_index;  //neuron's index number
        vector<double> N_weights;  //weights for next layer
        //function to return random values for weights
        double randomWeight(void);
        //private function to return value in between -1 & 1
        double transferFunction(double x);
};

#endif // NEURON_H
