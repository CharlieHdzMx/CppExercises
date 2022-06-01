#pragma once
#include "..\GraphLib\Vertex.h"
#include "..\GraphLib\GraphManager.h"
#include "NeuronalNetwork.h"
#include <vector>
#include "Axon.h"

using namespace std;


class CNeuronalNetwork;

class CNeuron :
	public CVertex
{
public:
	CNeuron();

	virtual ~CNeuron();

	void Dot();

	void Serialize(fstream& io, bool bSave);

	vector<float> m_vW;

	vector<CAxon*> m_vInputs;

	float m_fNeuronOutput;

	CNeuronalNetwork* m_pNN;

	float m_fError;

};

