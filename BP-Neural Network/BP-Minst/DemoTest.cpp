#include<iostream>
#include<vector>
#include<cassert>

using namespace std;

struct Connection
{
	double weight;
	double deltaWeight;
};

class Neuron;
typedef vector<Neuron> Layer;

class Neuron
{
public:
	Neuron(unsigned numOutputs);
	void setOutputValue(double value) { outputValue = value; }
	double getOutputValue() const { return outputValue; }
	void feedForwrd(Layer &prevLayer);

private:
	static double randomWeight()
	{
		return rand() / double(RAND_MAX);
	}
	double outputValue;
	vector<Connection> outputWeights;
};

Neuron::Neuron(unsigned numOutputs)
{
	for (unsigned c = 0; c < numOutputs; c++)
	{
		outputWeights.push_back(Connection());
		outputWeights.back().weight = randomWeight();
	}
}

void Neuron::feedForwrd(Layer & prevLayer)
{
	double sum = 0;

	for (int i = 0; i < prevLayer.size(); i++)
	{
		sum += prevLayer[i].getOutputValue();
	}
}




class Net
{
public:
	Net(const vector<unsigned> &topology);
	void FeedForward(const vector<double> &inputValues);
	void backProp(const vector<double> &targetValues);
	void getResults(vector<double> &resultValues) const;

private:
	vector<Layer> myLayers;

};


Net::Net(const vector<unsigned>& topology)
{
	unsigned numLayers = topology.size();

	for (unsigned layerNum = 0; layerNum < numLayers; layerNum++)
	{
		myLayers.push_back(Layer());
		unsigned numOutput = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++)
		{
			myLayers.back().push_back(Neuron(numOutput));
			cout << "Create a Neuron" << endl;
		}
	}
}

void Net::FeedForward(const vector<double> &inputValue)
{
	assert(inputValue.size() == myLayers[0].size() - 1);

	for (int i = 0; i < inputValue.size(); i++)
	{
		myLayers[0][i].setOutputValue(inputValue[i]);
	}

	for (int layerNum = 1; layerNum < myLayers.size(); layerNum++)
	{
		Layer &prevLayer = myLayers[layerNum - 1];
		for (int n = 0; n < myLayers[layerNum].size() - 1; n++)
		{
			myLayers[layerNum][n].feedForwrd(prevLayer);
		}
	}
}

int main()
{
	vector<unsigned> topology;

	topology.push_back(3);
	topology.push_back(2);
	topology.push_back(1);

	Net myNet(topology);
	vector<double> inputValues;
	myNet.FeedForward(inputValues);

	vector<double> targetValues;
	myNet.backProp(targetValues);

	vector<double> resultValues;
	myNet.getResults(resultValues);
	system("pause");
	return 0;
}


