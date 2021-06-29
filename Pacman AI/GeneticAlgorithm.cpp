#include <iostream>
#include <vector>
#include <algorithm>

#include "GeneticAlgorithm.h"
#include "DNA.h"
#include "Network.h"

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(unsigned popSIZE, float mutate, vector<int> &fitness, vector<unsigned> &topo, vector<Network*> &net)
{
    populationSize = popSIZE;  //save population size (number of games)
    mutationProbability = mutate;  //save mutation rate
    fitnessScores = fitness;  //save high scores (not sure if can straight use vector)
    topology = topo;  //save topology
    networks = net;  //save all networks
}

GeneticAlgorithm::~GeneticAlgorithm(void)
{
    population.clear();  //delete everything
}

//create population of DNAs
void GeneticAlgorithm::initializePopulation()
{
    for(unsigned i = 0; i < populationSize; i++)
    {
        population.push_back(new DNA(topology));  //create a new DNA to population
        population.at(i)->neuralNetwork = networks.at(i);  //pass saved network to the DNA
    }
}

//run genetic process
void GeneticAlgorithm::runGenetic()
{
    //update fitness scores for each DNA
    for(unsigned i = 0; i < population.size(); i++)
    {
        updateFitness(population[i], i);
    }

    //sort the DNA according to top
    selectionSort();

    //produce children
    generateNew();

}

//set fitness of the DNA
void GeneticAlgorithm::updateFitness(DNA* chromosome, unsigned index)
{
    chromosome->fitness = fitnessScores[index];
}

//sort and select the top DNAs
void GeneticAlgorithm::selectionSort()
{
    //sort whole population using comparator function
    sort(population.begin(), population.end(), comparator);

    //only select top 20% of population
    unsigned top = populationSize * 0.2;
    //delete everything else behind
    population.erase(population.begin()+top, population.end());
}

//function of how to sort the DNA (compare fitness)
bool GeneticAlgorithm::comparator(DNA* a, DNA* b)
{
    return (b->fitness) < (a->fitness);
    //a > b (descending order)
}

//produce children with the selected DNAs
void GeneticAlgorithm::generateNew()
{
    //20% of top fitness parents
    int top = populationSize * 0.2;

    //crossover until 60% of the population is new children
    int maxChildren = populationSize*0.6;
    for(unsigned i = 0; i < maxChildren; i++)
    {
        //choose random 2 parents
        int randomNum1 = rand()%top;
        int randomNum2 = rand()%top;
        //the children add behind the top population parents
        DNA* temp = crossover(population[randomNum1], population[randomNum2]);
        population.push_back(temp);

        //mutate the 60% children generated
        mutation(population.at(i+top));
    }

    //fill in the remaining 20% with random DNA
    while(population.size() < populationSize)
    {
        //pass in an example parent for getting total number of weights
        population.push_back(generateRandomChild(population[0]));
    }
}

//get 2 parents DNA to crossover for a children
DNA* GeneticAlgorithm::crossover(DNA* parent1, DNA* parent2)
{
    DNA* child = new DNA(topology);
    vector<double> childWeights;
    //get the weights of the parents
    vector<double> parent1Weights = parent1->networkToWeights(parent1->neuralNetwork);
    vector<double> parent2Weights = parent2->networkToWeights(parent2->neuralNetwork);

    //choose a crossover point randomly
    unsigned point = rand() % parent1Weights.size();

    //go through each weight
    for(unsigned i = 0; i < parent1Weights.size(); i++)
    {
        //left side of the point
        if(i < point)
            //set the specific child weight to specific parent weight
            childWeights.push_back(parent1Weights[i]);
        //right side of the point
        else
            childWeights.push_back(parent2Weights[i]);
    }
    //set the child weights into the child network
    child->neuralNetwork = child->weightsToNetwork(childWeights, topology);

    return child;
}

//determine to mutate weight or not depending on mutation rate
void GeneticAlgorithm::mutation(DNA* chromosome)
{
    //get the weights of DNA
    Network* temp = chromosome->neuralNetwork;
    vector<double> weights = chromosome->networkToWeights(temp);

    //go through each weights
    for(unsigned i = 0; i < weights.size(); i++)
    {
        //generate a random number to compare with mutation rate
        float randomNum = rand()/float(RAND_MAX + 1.0);
        //if higher than mutation rate
        if(randomNum > mutationProbability)
            //change the weight to a random weight
            weights.at(i) = rand()/double(RAND_MAX + 1.0);
    }
}

//generate totally random weights to fill in the rest of population
DNA* GeneticAlgorithm::generateRandomChild(DNA* parent)
{
    DNA* child = new DNA(topology);

    vector<double> childWeights;
    //get an example parent for total number of weights needed to be generated
    vector<double> parentWeights = parent->networkToWeights(parent->neuralNetwork);

    //generate random weights
    for(unsigned i = 0; i < parentWeights.size(); i++)
    {
        childWeights.push_back(rand() / double(RAND_MAX));
    }

    //save weights to the child network
    child->weightsToNetwork(childWeights, topology);

    return child;
}

//function to return the next generation population to main
vector<Network *> GeneticAlgorithm::return_nHolder()
{
    vector<Network *> network;

    for(int i = 0; i < populationSize; i++)
    {
        DNA* temp = population.at(i);
        network.push_back(temp->neuralNetwork);
    }
    return network;
}

