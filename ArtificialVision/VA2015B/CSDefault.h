#pragma once

#include "DXGIManager.h"
#include "matrix.h"

class CCSDefault
{
public:
	CCSDefault(CDXGIManager* pOwner);
	~CCSDefault();

	bool initialize();
	void uninitialize();
	void configure();
	void execute();

	ID3D11Texture2D* m_pInput;
	ID3D11Texture2D* m_pOutput;

	struct PARAMS{
		MATRIX4D T;
		float time;
	}m_PARAMS;

protected:
	CDXGIManager* m_pOwner;
	ID3D11ComputeShader* m_pCS;
	ID3D11Buffer* m_pCB;

	//Tareas de D11
};

