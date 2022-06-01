#pragma once
#include "DXGIManager.h"
#include "matrix.h"
#include <vector>

using namespace std;

class CCSALU
{
protected:
	CDXGIManager* m_pOwner;
	ID3D11ComputeShader* m_pCS;
	ID3D11Buffer* m_pCB;
	vector<ID3D11ComputeShader*> m_vCS;
public:
	ID3D11Texture2D* m_pInputA;
	ID3D11Texture2D* m_pInputB;
	ID3D11Texture2D* m_pOutput;

	struct PARAMS{
		unsigned int option;
		float threshold;
	}m_Params;

	bool initialize();
	void unitialize();
	void configure();
	void execute();

	CCSALU(CDXGIManager* m_pOwner);
	CCSALU();
	~CCSALU();
};

