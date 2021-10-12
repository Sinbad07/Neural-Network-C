#pragma once

#ifndef NET_H
#define NET_H

#include <vector>
#include <iostream>
#include <fstream>
#include "Neuron.h"
using namespace std;

// to improve readability, using typedef here lets me reference Layers 
typedef vector<Neuron> Layer;

// Class for neural network with related methods
class Net
{
public:

    // constructor needs to know the number of neurons and layers (topology)
    // These neurons are arranged in columns and rows
    // hence the need for a 2D vector for input
    Net(const vector<int> &topology);

    // method for supplying information to the neurons
    // only needs to read data, hence const
    void feedForward(const vector<double> &inputVals);

    // Method for the 'learning' part of the neural network
    // allows the neural network to check input values against output values
    // this uses weights to calculate a mathematical function
    // which increases in accuracy in proportion to the amount of data
    //
    // read only, hence const
    void backPropogation(const vector<double> &targetVals);

    // method for retrieving values.
    // getResults doesn't modify variables at all so using const here
    void getResults(vector<double> &resultVals) const;

private:

    // Network will be made up of layers and neurons
    // within each layer will be multiple neurons
    // multiple layers will make up a Net
    // e.g. netlayers[layers][neurons]
    vector<Layer> netLayers;

    // Root Mean Square error used to calculate net error
    double RMSError;
    double netAverageError;
    double netAverageSmoothingFactor;
};

#endif