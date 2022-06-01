#pragma once
#include "Axon.h"

class CAxonInput :
	public CAxon
{
public:

	CAxonInput();
	virtual ~CAxonInput();

	virtual void Eval(){};
};

