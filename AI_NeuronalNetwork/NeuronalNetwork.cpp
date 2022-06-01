#include "stdafx.h"
#include "NeuronalNetwork.h"
#include "AxonInput.h"

CNeuronalNetwork::CNeuronalNetwork()
{
	m_AxonBias.m_fOutput = 1;
	m_pAxonBias = &m_AxonBias;
}


CNeuronalNetwork::~CNeuronalNetwork()
{
	for (auto itL = m_vLayers.begin(); itL != m_vLayers.end(); itL++)
	{
		for (auto itN = itL->Neurons.begin(); itN != itL->Neurons.end(); itN++)
			delete(*itN);

		for (auto itA = itL->Axons.begin(); itA != itL->Axons.end(); itA++)
			delete(*itA);

		itL->Neurons.clear();
		itL->Axons.clear();
	}
}

void CNeuronalNetwork::Connect(unsigned int uiNeurons, CAxon* pAxon){

	if (m_vLayers.size())
	{
		m_vLayers[0].Neurons[uiNeurons]->m_vInputs[0] = pAxon;
	}
}

void CNeuronalNetwork::Eval(void){
	//Suponer red neuronla consistente y teselada previamente.
	//La capa de entrada ya esta conectad a a otra subred evaluada o bien conectada a axones de entrada.
	//pesos previamente definidos

	for (auto itL = m_vLayers.begin(); itL != m_vLayers.end(); itL++)
	{
		for (unsigned int n = 0; n < itL->Neurons.size(); n++)
		{
			itL->Neurons[n]->Dot();
			itL->Axons[n]->Eval();
		}
	}

}

//Calcula los errores de cada neurona para implementarlas en el aprendizaje
float CNeuronalNetwork::Retropropragation(float* pArrayInputs, float* pArrayOutputs)
{
	//Retropropagacion por capa -neurona
	for (int i = (m_vLayers.size()-1); i >= 0 ; i--)
		for (unsigned int j = 0; j < m_vLayers[i].Neurons.size(); j++)
		{
			//Si la capa es la primera los errores son igual a la plantilla salida de cada axon de salida - la salida producida por eval
			if (i == (m_vLayers.size()-1))
				m_vLayers[i].Neurons[j]->m_fError = pArrayOutputs[j] - m_vLayers[i].Axons[j]->m_fOutput;

			//El error de neurona[n] Las demas capas son la suma del producto de el error de las neuronas de la capa posterior por el vector de pesos en[n]
			else
				for (unsigned int n = 0; n < m_vLayers[i + 1].Neurons.size(); n++)
					m_vLayers[i].Neurons[j]->m_fError += m_vLayers[i + 1].Neurons[n]->m_fError*m_vLayers[i + 1].Neurons[n]->m_vW[j];
		}

		float l_fNNError = 0.0f;

		for (unsigned int x = 0; x < m_vLayers[(m_vLayers.size()) - 1].Neurons.size(); x++)
			l_fNNError += pArrayOutputs[x] - m_vLayers[(m_vLayers.size()) - 1].Axons[x]->m_fOutput;

		l_fNNError = l_fNNError / m_vLayers[(m_vLayers.size()) - 1].Neurons.size();

		return l_fNNError;
}



// Actualiza los pesos de cada neurona tomando en cuenta los errores de cada neurona calculados en la retropropagacion
void CNeuronalNetwork::Reappraise(float CteofError)
{
	for (unsigned int i = 0; i < m_vLayers.size(); i++)
		for (unsigned int j = 0; j < m_vLayers[i].Neurons.size();j++)
			for (unsigned int n = 0; n < m_vLayers[i].Neurons[j]->m_vW.size(); n++)
				m_vLayers[i].Neurons[j]->m_vW[n] += m_vLayers[i].Neurons[j]->m_fError*CteofError*m_vLayers[i].Neurons[j]->m_vInputs[n]->m_fOutput;

}


unsigned int CNeuronalNetwork::Learn(float* pArrayInputs, float* pArrayOutputs, float CteofError)
{
	float l_TemplateOutput = 0.0f;
	float l_NNError = 0.0f;
	unsigned int k = 0;

	for (unsigned long i = 0; i < m_vLayers[(m_vLayers.size()) - 1].Axons.size(); i++)
		l_TemplateOutput += pArrayOutputs[i];

	l_TemplateOutput = l_TemplateOutput / m_vLayers[(m_vLayers.size()) - 1].Axons.size();

	do
	{
		Eval();
		l_NNError = Retropropragation(pArrayInputs, pArrayOutputs);
		Reappraise(CteofError);
		k++;
	} while (!(abs(l_NNError)<=0.002));

	return k;
}
