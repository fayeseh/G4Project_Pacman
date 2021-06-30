#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "DNA.h"
#include "Network.h"
#include <iostream>
#include <vector>

using namespace std;

class DNA;  //includes neural network & fitness
class Network;

class GeneticAlgorithm
{
    public:
        GeneticAlgorithm(unsigned popSIZE, float mutate, vector<int> &fitness, vector<unsigned> &topo, vector<Network*> &net, unsigned ID);  //constructor
        ~GeneticAlgorithm(void);  //destructor
        void initializePopulation();  //create population of DNAs
        void runGenetic();  //run genetic process
        void updateFitness(DNA* chromosome, unsigned index);  //high score of the game
        void selectionSort();  //sort elite fitness (top)
        static bool comparator(DNA* a, DNA* b);  //for sorting the DNA fitness
        void generateNew();  //produce children with the selected DNAs
        DNA* crossover(DNA* parent1, DNA* parent2);  //reproduction, propagate
        void mutation(DNA* chromosome);  //determine to mutate weight or not depending on mutation rate
        DNA* generateRandomChild(DNA* parent);  //new children with random DNA
        vector<Network*> return_nHolder();  //function to return the next generation population to main
        void writeToFile();

        unsigned populationSize;
        float mutationProbability;
        vector<DNA*> population;
        vector<int> fitnessScores;
        vector<unsigned> topology;
        vector<Network*> networks;
        unsigned fileID;

    private:

};

#endif // GENETICALGORITHM_H
