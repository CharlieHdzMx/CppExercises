#pragma once
#include "DXGIManager.h"
#include "matrix.h"


class CCSConvolution
{
protected:
	CDXGIManager* m_pOwner;
	ID3D11ComputeShader* m_pCS;
	ID3D11Buffer* m_pCB;

public:
	ID3D11Texture2D* m_pInput;
	ID3D11Texture2D* m_pOutput;
	struct PARAMS{
		MATRIX4D Kernel;
		VECTOR4D C;
	}m_Params;//Buffer de parametros

public:
	CCSConvolution(CDXGIManager* m_pOwner);
	~CCSConvolution();
	bool initialize();
	void unitialize();
	void Configure();
	void execute();
};

