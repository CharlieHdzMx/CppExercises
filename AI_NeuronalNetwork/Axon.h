#pragma once
class CNeuron;

class CAxon
{

public:
	CAxon();
	virtual ~CAxon();

	virtual void Eval() = 0;

	CNeuron* pNeuronOwner;

	float m_fOutput;
};

