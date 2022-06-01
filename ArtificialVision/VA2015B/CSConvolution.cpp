#include "stdafx.h"
#include "CSConvolution.h"


CCSConvolution::CCSConvolution(CDXGIManager* pOwner)
{
	m_pOwner = pOwner;
	m_pCS = 0;
	m_pCB = 0;
	memset(&m_Params, 0, sizeof(PARAMS));
}

bool CCSConvolution::initialize(){
	m_pCS=m_pOwner->CompileCS(L"..\\Shaders\\Convolution.hlsl", "Main");
	if (!m_pCS)
		return false;
	D3D11_BUFFER_DESC dbd;
	memset(&dbd, 0, sizeof(dbd));
	dbd.Usage = D3D11_USAGE_DYNAMIC;
	dbd.ByteWidth = 16 * ((sizeof(PARAMS)+15) / 16);
	dbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	dbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	if (FAILED(m_pOwner->getDevice()->CreateBuffer(&dbd, 0, &m_pCB))){
		SAFE_RELEASE(m_pCS);
		return false;
	}
	return true;
}

void CCSConvolution::Configure(){
	D3D11_MAPPED_SUBRESOURCE ms;
	m_pOwner->getContext()->Map(m_pCB, 0,D3D11_MAP_WRITE_DISCARD, 0, &ms);
	memcpy(ms.pData, &m_Params,sizeof(PARAMS));
	m_pOwner->getContext()->Unmap(m_pCB, 0);

	ID3D11ShaderResourceView* pSRV = 0;
	ID3D11UnorderedAccessView* pUAV = 0;
	m_pOwner->getDevice()->CreateShaderResourceView(m_pInput, NULL, &pSRV);
	m_pOwner->getDevice()->CreateUnorderedAccessView(m_pOutput, NULL, &pUAV);

	m_pOwner->getContext()->CSSetConstantBuffers(0, 1, &m_pCB);
	m_pOwner->getContext()->CSSetUnorderedAccessViews(0, 1, &pUAV,NULL);
	m_pOwner->getContext()->CSSetShaderResources(0, 1, &pSRV);
	m_pOwner->getContext()->CSSetShader(m_pCS, NULL, NULL);
	SAFE_RELEASE(pSRV);
	SAFE_RELEASE(pUAV);
}

void CCSConvolution::execute(){

	int gx, gy;
	D3D11_TEXTURE2D_DESC dtd;
	m_pOutput->GetDesc(&dtd);
	gx = ((dtd.Width + 7) / 8);
	gy = ((dtd.Height + 7) / 8);
	m_pOwner->getContext()->Dispatch(gx, gy, 1);
	m_pOwner->getContext()->Flush();
	m_pOwner->getContext()->ClearState();
}

void CCSConvolution::unitialize(){
	SAFE_RELEASE(m_pCS);
	SAFE_RELEASE(m_pCB);
}

CCSConvolution::~CCSConvolution()
{
	unitialize();
}
