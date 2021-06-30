#include "Game.h"
#include "Network.h"
#include "GeneticAlgorithm.h"

#include <thread>

using namespace std;

void createGame(CConsoleLoggerEx *Logger, Network *net, int &high) {
    //run pacman game
    Game* game = new Game(net, Logger);
    game->Go(high);
    delete game;
}

int main() {

    unsigned population = 25;
    float mutationRate = 0.3;

    Network* nHolder[population];  //network holder
    int fHolder[population];  //for pass by reference high score
    CConsoleLoggerEx* cHolder[population];  //console holder

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

    //create array of network
        for(int i = 0; i < population; i++)
        {
            Network *testNet = new Network(topology);
            nHolder[i] = testNet;
        }

    //create consoles
    for(int i = 0; i < population; i++) {
        CConsoleLoggerEx* cx = new CConsoleLoggerEx();
        cx->Create("PACMAN");
        cHolder[i] = cx;
    }

    unsigned generation = 0;
    while(true)
    {
        cout << endl << "===Generation " << generation << "===" << endl;
        thread t1(createGame, cHolder[0], nHolder[0], ref(fHolder[0]));
        thread t2(createGame, cHolder[1], nHolder[1], ref(fHolder[1]));
        thread t3(createGame, cHolder[2], nHolder[2], ref(fHolder[2]));
        thread t4(createGame, cHolder[3], nHolder[3], ref(fHolder[3]));
        thread t5(createGame, cHolder[4], nHolder[4], ref(fHolder[4]));
        thread t6(createGame, cHolder[5], nHolder[5], ref(fHolder[5]));
        thread t7(createGame, cHolder[6], nHolder[6], ref(fHolder[6]));
        thread t8(createGame, cHolder[7], nHolder[7], ref(fHolder[7]));
        thread t9(createGame, cHolder[8], nHolder[8], ref(fHolder[8]));
        thread t10(createGame, cHolder[9], nHolder[9], ref(fHolder[9]));
        thread t11(createGame, cHolder[10], nHolder[10], ref(fHolder[10]));
        thread t12(createGame, cHolder[11], nHolder[11], ref(fHolder[11]));
        thread t13(createGame, cHolder[12], nHolder[12], ref(fHolder[12]));
        thread t14(createGame, cHolder[13], nHolder[13], ref(fHolder[13]));
        thread t15(createGame, cHolder[14], nHolder[14], ref(fHolder[14]));
        thread t16(createGame, cHolder[15], nHolder[15], ref(fHolder[15]));
        thread t17(createGame, cHolder[16], nHolder[16], ref(fHolder[16]));
        thread t18(createGame, cHolder[17], nHolder[17], ref(fHolder[17]));
        thread t19(createGame, cHolder[18], nHolder[18], ref(fHolder[18]));
        thread t20(createGame, cHolder[19], nHolder[19], ref(fHolder[19]));
        thread t21(createGame, cHolder[20], nHolder[20], ref(fHolder[20]));
        thread t22(createGame, cHolder[21], nHolder[21], ref(fHolder[21]));
        thread t23(createGame, cHolder[22], nHolder[22], ref(fHolder[22]));
        thread t24(createGame, cHolder[23], nHolder[23], ref(fHolder[23]));
        thread t25(createGame, cHolder[24], nHolder[24], ref(fHolder[24]));

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();
        t8.join();
        t9.join();
        t10.join();
        t11.join();
        t12.join();
        t13.join();
        t14.join();
        t15.join();
        t16.join();
        t17.join();
        t18.join();
        t19.join();
        t20.join();
        t21.join();
        t22.join();
        t23.join();
        t24.join();
        t25.join();

        //convert array to vector for network
        vector<Network*> networks;
        for(int i = 0; i < population; i++)
        {
            networks.push_back(nHolder[i]);
        }

        //convert array to vector for fitness
        vector<int> fitness;
        for(int i = 0; i < population; i++)
        {
            fitness.push_back(fHolder[i]);
            cout << "High Score " << i+1 << ": " << fitness.at(i) << endl;
        }

        GeneticAlgorithm testGen(population, mutationRate, fitness, topology, networks, generation);
        //cout << "Done construct" << endl;
        testGen.initializePopulation();
        //cout << "Done initialize" << endl;
        testGen.runGenetic();
        cout << "Genetic Done Running" << endl;

        networks = testGen.return_nHolder();
        //cout << "Done saving" << endl;

        //save vector to network holder
        for(int i = 0; i < population; i++)
        {
            nHolder[i] = networks.at(i);
        }
        generation++;
    }

    return 0;
}

//multithread
