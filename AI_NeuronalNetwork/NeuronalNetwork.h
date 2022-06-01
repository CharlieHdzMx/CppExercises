#pragma once
#include "..\GraphLib\Graph.h"
#include <vector>
#include "Axon.h"
#include "Neuron.h"
#include "AxonInput.h"

using namespace std;

typedef vector<CNeuron*> CNeuronLayer;
typedef vector<CAxon*> CAxonLayer;

class CNeuronalNetwork :
	public CGraph
{
public:
	CNeuronalNetwork();
	~CNeuronalNetwork();

	void Connect(unsigned int uiNeuron, CAxon* pAxon);

	struct NPAIR
	{
		CNeuronLayer Neurons;
		CAxonLayer Axons;
	};
	vector<NPAIR> m_vLayers;

	CAxonInput m_AxonBias;

	CAxonInput* m_pAxonBias;

	void Eval(void);

	float Retropropragation(float* pArrayInputs, float* pArrayOutputs);
	// Reevalua la red neuronal integrando los errores de cada neurona calculados en retropropagation
	void Reappraise(float CteofError);

	//bool Learn (float* pArrayInputs,float* pArrayOutputs,float CteofError);
	unsigned int Learn(float* pArrayInputs, float* pArrayOutputs, float CteofError);
};

