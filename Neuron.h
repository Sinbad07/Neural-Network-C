#pragma once

#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

typedef vector<Neuron> Layer;

// Class for Neurons with related methods 
class Neuron
{
public:
	// upon construction, the neuron needs to know the number of outputs in the next layer
	Neuron(int outputNum, int neuronIndex);
	
	// method for calculating and executing a Feed Foward algorithm
	void feedForward(Layer&prevLayer);
	 
	// Incapsulation methods for setting/ retrieving data
	void setOutputVal(double val);
	// const because nothing is being changed
	double getOutputVal() const;


private:
	
	// using static here I want the random generation the same way every time
	static double randomWeight();
	static double activationFunction(double x);
	static double activationFunctionDerivative(double x);
	// required variables for computation
	double neuronOutputVal;
	vector<double> neuronOutputWeights;
	int neuronIndex;

};

#endif