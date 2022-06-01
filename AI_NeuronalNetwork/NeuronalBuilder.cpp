#include "stdafx.h"
#include "NeuronalBuilder.h"
#include "AxonSigmoid.h"
#include "AxonStep.h"
#include "AxonInput.h"


CNeuronalBuilder::CNeuronalBuilder()
{
}


CNeuronalBuilder::~CNeuronalBuilder()
{
}


CNeuronalNetwork* CNeuronalBuilder::CreateMultiLayerNetwork(unsigned int nLayers, unsigned int* pnNeuronsPerLayer, char**	pcAxonTypePerLayer){
	
	CNeuronalNetwork* pNN=new CNeuronalNetwork;
	
	pNN->m_vLayers.resize(nLayers);

	for (unsigned int n = 0; n < nLayers; n++)
	{
		pNN->m_vLayers[n].Neurons.resize(pnNeuronsPerLayer[n]);
		pNN->m_vLayers[n].Axons.resize(pnNeuronsPerLayer[n]);

		for (unsigned int j = 0; j < pnNeuronsPerLayer[n]; j++)
		{
			//Crear Neurona
			pNN->m_vLayers[n].Neurons[j] = new CNeuron;

			//Crear Axon
			if (strcmp("CAxonStep", pcAxonTypePerLayer[n]) == 0)
				pNN->m_vLayers[n].Axons[j] = new CAxonStep;

			else if (strcmp("CAxonSigmoid", pcAxonTypePerLayer[n]) == 0)
				pNN->m_vLayers[n].Axons[j] = new CAxonSigmoid;

			else
				*(int*) 0 = 0;

			//Conectar Axon con Neurona
			pNN->m_vLayers[n].Axons[j]->pNeuronOwner = pNN->m_vLayers[n].Neurons[j];
			//Asignar recursos para el vector de pesos de cada neurona y para cada axon que alimentan a cada neurona

			if (n == 0)
			{
				pNN->m_vLayers[n].Neurons[j]->m_vInputs.resize(2);
				pNN->m_vLayers[n].Neurons[j]->m_vW.resize(2);
			}

			else{
				pNN->m_vLayers[n].Neurons[j]->m_vInputs.resize((pnNeuronsPerLayer[n - 1])+1);
				pNN->m_vLayers[n].Neurons[j]->m_vW.resize((pnNeuronsPerLayer[n - 1])+1);
			}

			//Alternativas para crear una red neuronal entrenada
			//a).- Se puede predefinir valores de manera sistemica  determinada
			//b).- Se pueden predefinir valores de manera aleatoria

			//alternativa b) una red neuronal nueva, sin arquetipos nuevos

			for (unsigned int i = 0; i < pNN->m_vLayers[n].Neurons[j]->m_vW.size(); i++)
			{
				pNN->m_vLayers[n].Neurons[j]->m_vW[i]=2*(rand() / (float) (RAND_MAX))-1;
			}
			//Ha nacido una red neuronal estúpida.
		}
	}
	//Crear el axon comun, con estimulos de entrada 1 y conectar con las dentritas 
	//a todas las neuronas de la red neuronal
	//Instanciarlo como mienbro de la red neuronal 
	return pNN;
}

void CNeuronalBuilder::Tesselate(CNeuronalNetwork* pNN){
	//Por capa-Neurona
	for (unsigned int n = 1; n < pNN->m_vLayers.size();++n)
			for (unsigned int j = 0; j < pNN->m_vLayers[n].Neurons.size(); ++j)
			{
				int k=0;
				for (auto it = pNN->m_vLayers[n - 1].Axons.begin(); it != pNN->m_vLayers[n - 1].Axons.end();k++, ++it)
					pNN->m_vLayers[n].Neurons[j]->m_vInputs[k]=(*it);

			}

			//Conectar Axon Bias
			for (unsigned int y = 0; y < pNN->m_vLayers.size(); ++y)
				for (unsigned int x = 0; x < pNN->m_vLayers[y].Neurons.size(); ++x)
				{
					
					if (y != 0)
						pNN->m_vLayers[y].Neurons[x]->m_vInputs[pNN->m_vLayers[y-1].Neurons.size()]=pNN->m_pAxonBias;

					else
						pNN->m_vLayers[y].Neurons[x]->m_vInputs[1]=pNN->m_pAxonBias;

				}
}
