#pragma once
#include "NeuronalNetwork.h"


class CNeuronalBuilder
{
public:
	CNeuronalBuilder();
	~CNeuronalBuilder();
	
	CNeuronalNetwork* CreateMultiLayerNetwork(unsigned int nLayers,unsigned int* pnNeuronsPerLayer,char**		pcAxonTypePerLayer);

	void Tesselate(CNeuronalNetwork* pNNToTesselate);
};

