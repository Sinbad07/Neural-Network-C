// required for variable length multi-dimensional arrays that the network needs
#include <vector>
#include <iostream>
#include <fstream>
#include "Net.h"
#include "Neuron.h"
using namespace std;

// to improve readability, using typedef here lets me reference Layers
typedef vector<Neuron> Layer;


int main()
{

    // vector required for constructor to adjust neural network size and topology
    vector<int> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);

    Net myNet(topology);

    // since the net will change size, I need a dynamically allocated memory
    // hence, the use of a vector here.
    vector<double> inputVals;
    myNet.feedForward(inputVals);

    vector<double> targetVals;
    myNet.backPropogation(targetVals);

    vector<double> resultVals;
    myNet.getResults(resultVals);


    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu