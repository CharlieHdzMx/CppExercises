#include "stdafx.h"
#include "AxonSigmoid.h"
#include "Neuron.h"


CAxonSigmoid::CAxonSigmoid()
{
}


CAxonSigmoid::~CAxonSigmoid()
{
}

void CAxonSigmoid::Eval(){

	m_fOutput = 0;

	m_fOutput = (2 / (1 + exp(-pNeuronOwner->m_fNeuronOutput)))-1;
}