#include "stdafx.h"
#include "Neuron.h"
#include <algorithm>

using namespace std;

CNeuron::CNeuron()
{
}


CNeuron::~CNeuron()
{
}


// Realiza el computo del hiperplano Dot(I,W,n)
void CNeuron::Dot()
{
	if (m_vW.size() == m_vInputs.size())
	{
		m_fNeuronOutput = 0;
		for (int i = 0; i < m_vW.size(); i++)
			m_fNeuronOutput += m_vW[i] * m_vInputs[i]->m_fOutput;
	}

	else
		*(int*) 0 = 0;

}


void CNeuron::Serialize(fstream& io, bool bSave)
{

}	
