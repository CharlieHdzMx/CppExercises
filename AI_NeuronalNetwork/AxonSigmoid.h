#pragma once
#include "Axon.h"
#include <cmath>

using namespace std;

class CAxonSigmoid :
	public CAxon
{
public:
	CAxonSigmoid();
	virtual ~CAxonSigmoid();

protected:
	virtual void Eval();

};

