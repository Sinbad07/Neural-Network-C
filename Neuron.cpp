#include "Neuron.h"
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

Neuron::Neuron(int outputNum, int neuronID)
{
	
	for (int connections = 0; connections < outputNum; connections++)
	{
		// appending the number of connections to each neuron
		neuronOutputWeights.push_back(Connection());

		// set random weight to last connection made, hence .back()
		// using custom psuedorandom number generation hence own function
		neuronOutputWeights.back().weight = randomWeight();
	}

	neuronIndex = neuronID;
}

double Neuron::randomWeight(void)
{
	// generate a random number between 0 and 1
	// since you're dividing by the max value,
	// the value will always be between 0 and 1
	return rand() / double(RAND_MAX);
}

double Neuron::activationFunction(double x)
{
	// using a hyperbolic tan (tanh) function that gives a value between -1 and 1
	return tanh(x);
}

double Neuron::activationFunctionDerivative(double x)
{
	//derivative of tanh
	return 1.0 - tanh(x) * tanh(x);
}

void Neuron::feedForward(Layer& prevLayer)
{
	// apply feed forward algorithm
	// sum the previous layer's outputs
	double sum{ 0.0 };

	for (int neuron = 0; neuron < prevLayer.size(); neuron++)
	{
		sum += prevLayer[neuron].neuronOutputVal *
			prevLayer[neuron].neuronOutputWeights[neuronIndex].weight;
	}

	// apply activation function 
	neuronOutputVal = activationFunction(sum);

}


void Neuron::setOutputVal(double val)
{
	neuronOutputVal = val;
}

double Neuron::getOutputVal() const
{
	return neuronOutputVal;
}