#include "stdafx.h"
#include "AxonStep.h"
#include "Neuron.h"


CAxonStep::CAxonStep()
{
}


CAxonStep::~CAxonStep()
{
}

void CAxonStep::Eval(){

	m_fOutput = 0;

	m_fOutput=((pNeuronOwner->m_fNeuronOutput > 0) ? 1 : -1);
}