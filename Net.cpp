#include "Net.h"
#include "Neuron.h"
#include <assert.h> // for error checking
#include <vector>
using namespace std;

// to improve readability, using typedef here lets me reference Layers 
typedef vector<Neuron> Layer;

Net::Net(const vector<int> &topology)
{
	//initialize number of layers from size
	int numLayers = topology.size();

	// fill each layer with neurons
	for (int layerNum = 0; layerNum < numLayers; layerNum++)
	{
		//creating each layer
		netLayers.push_back(Layer());

		// determining the number of output connections
		int outputNum = topology[layerNum + 1];

		// if it's the output neuron, it will have no output connections
		if (layerNum == topology.size() - 1)
		{
			outputNum = 0;
		}

		//add neurons + bias neuron to each layer (hence <= instead pf <)
		for (int neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++)
		{
			netLayers.back().push_back(Neuron(outputNum, neuronNum));
			// debug code to check neuron initialization
			cout << "Neuron number " << neuronNum << " in layer " << layerNum << endl;
		}
	}
}

void Net::feedForward(const vector<double> &inputVals)
{
	// error check first that there are the right number of input neurons (-1 for bias neuron)
	assert(inputVals.size() == netLayers[0].size() - 1);

	// assign the values to neurons
	for (int input = 0; input < inputVals.size(); input++)
	{
		netLayers[0][input].setOutputVal(inputVals[input]);
	}

	// starting on 1 becuase feeding forward requires previous layer
	// applying Feed Foward algorithm for each network layer...
	for (int layerNum = 1; layerNum < netLayers.size(); layerNum++)
	{
		// ...and for each neuron (-1 for bias)
		Layer &prevLayer = netLayers[layerNum - 1];
		for (int neuronNum = 0; neuronNum < netLayers[layerNum].size() - 1; neuronNum++)
		{
			netLayers[layerNum][neuronNum].feedForward(prevLayer);
		}
	}
}

void Net::backPropogation(const vector<double> &targetVals)
{
	// Calculate overall network error or Root Mean Square of output neuron errors
	RMSError = 0.0;

	// assign last layer as output layer
	Layer& outputLayer = netLayers.back();

	// loop through all neurons (except bias)
	for (int neuron = 0; neuron < outputLayer.size() - 1; neuron++)
	{
		// errorDelta here is the difference between expected and actual values
		double errorDelta = targetVals[neuron] - outputLayer[neuron].getOutputVal();
		RMSError += errorDelta * errorDelta;
	}
	RMSError /= outputLayer.size() - 1; // mean error squared, then rooted
	RMSError = sqrt(RMSError);

	// check error against multiple training samples
	netAverageError =
		(netAverageError * netAverageSmoothingFactor + RMSError)
		/ (netAverageSmoothingFactor + 1.0);

	// calculate output layer gradients (except bias)

	for (int neuron = 0; neuron < outputLayer.size() - 1; neuron++)
	{
		outputLayer[neuron].calcOutputGradients(targetVals[neuron]);

	}

	// calculate gradients on hidden layers

	for (int layerNum = netLayers.size() - 2; layerNum > 0; layerNum--)
	{
		Layer& hiddenLayer = netLayers[layerNum];
		Layer& nextLayer = netLayers[layerNum + 1];

		for (int neuron = 0; neuron < hiddenLayer.size(); neuron++)
		{
			hiddenLayer[neuron].calcHiddenGradients(nextLayer);
		}
	}

	// for all layers from outputs to first hidden layer,
	// update connection weights

	for (int layerNum = netLayers.size - 1; layerNum > 0; layerNum--)
	{
		Layer& layer = netLayers[layerNum];
		Layer& prevLayer = netLayers[layerNum - 1];
	}

}

void Net::getResults(vector<double> &resultVals) const
{

}