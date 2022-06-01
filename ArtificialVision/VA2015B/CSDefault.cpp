#include "stdafx.h"
#include "CSDefault.h"


CCSDefault::CCSDefault(CDXGIManager* pOwner)
{
	m_pOwner = pOwner;
	m_pCS = 0;
	m_pCB = 0;
	m_pInput = 0;
	m_pOutput = 0;
}

CCSDefault::~CCSDefault()
{
	uninitialize();
}

bool CCSDefault::initialize(){

	m_pCS = m_pOwner->CompileCS(L"..\\Shaders\\Default.hlsl", "CSMain");

	if (!m_pCS)
		return false;

	D3D11_BUFFER_DESC dbd;
	memset(&dbd, 0, sizeof(dbd));
	dbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	dbd.ByteWidth = 16 * ((sizeof(PARAMS)+15) / 16);
	//Multiplo de 16 bytes, si no fracasa.
	dbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	dbd.Usage = D3D11_USAGE_DYNAMIC;
	HRESULT hr = m_pOwner->getDevice()->CreateBuffer(&dbd, NULL, &m_pCB);

	if (FAILED(hr))
	{
		SAFE_RELEASE(m_pCS);
		return false;
	}
	return true;
}

void CCSDefault::configure(){

	ID3D11ShaderResourceView* pSVR = 0;//Entrada->Image Source
	ID3D11UnorderedAccessView* pUAV = 0;//Salida->Image Destiny.

	m_pOwner->getDevice()->CreateUnorderedAccessView(m_pOutput, NULL, &pUAV);
	m_pOwner->getDevice()->CreateShaderResourceView(m_pInput, NULL, &pSVR);

	m_pOwner->getContext()->CSSetShader(m_pCS, NULL, 0);
	m_pOwner->getContext()->CSSetShaderResources(0, 1, &pSVR);
	m_pOwner->getContext()->CSSetUnorderedAccessViews(0, 1, &pUAV, NULL);

	m_pOwner->getContext()->CSSetConstantBuffers(0, 1, &m_pCB);
	//Slot =b0.hsls Usar ese contexto como constant buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	m_pOwner->getContext()->Map(m_pCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
	//Se bloquea la lectura del cb, 
	{
		PARAMS params = m_PARAMS;
		params.T = transpose(m_PARAMS.T);
		memcpy(ms.pData, &params, sizeof(PARAMS));
	}
	m_pOwner->getContext()->Unmap(m_pCB, 0);

	SAFE_RELEASE(pUAV);
	SAFE_RELEASE(pSVR);
}

void CCSDefault::execute(){
	D3D11_TEXTURE2D_DESC dtd;
	m_pInput->GetDesc(&dtd);
	m_pOwner->getContext()->Dispatch((dtd.Width + 7) / 8, (dtd.Height + 7) / 8, 1);

	m_pOwner->getContext()->Flush();
	m_pOwner->getContext()->ClearState();
	//Limpiar configuracion
}

void CCSDefault::uninitialize(){
	SAFE_RELEASE(m_pCS);
	SAFE_RELEASE(m_pCB);
}

