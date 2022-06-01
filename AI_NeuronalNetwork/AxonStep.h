#pragma once
#include "Axon.h"

class CAxonStep :
	public CAxon
{
public:
	CAxonStep();

	virtual ~CAxonStep();

	virtual void Eval();
};

