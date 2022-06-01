#include "stdafx.h"
#include "CSALU.h"



CCSALU::CCSALU()
{
	
}

CCSALU::CCSALU(CDXGIManager* pOwner){
	m_pOwner = pOwner;
	m_pCS = 0;
	m_pCB = 0;
	memset(&m_Params, 0, sizeof(PARAMS));
}

bool CCSALU::initialize(){
	vector<char*> vMains;
	
	vMains = { "CopyMain", "NotMain","AndMain","OrMain","XorMain","SADDMain","SSUBMain","ModMain","ALPHAS0Main","ALPHAS1Main","HP_THRESHOLDMain","LP_THRESHOLDMain","MergeMain"};

	//Compilar todos los mains.
	for (unsigned int i = 0; i < vMains.size();i++){
		char* temp=vMains.at(i);
		m_pCS = m_pOwner->CompileCS(L"..\\Shaders\\CSALU.hlsl", temp);
		if (!m_pCS)
			return false;
		m_vCS.push_back(m_pCS);
	}
	
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

void CCSALU::configure(){
	//Seleccion de mains
	m_pCS = m_vCS.at(m_Params.option);

	D3D11_MAPPED_SUBRESOURCE ms;
	m_pOwner->getContext()->Map(m_pCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
	memcpy(ms.pData, &m_Params, sizeof(PARAMS));
	m_pOwner->getContext()->Unmap(m_pCB, 0);

	ID3D11ShaderResourceView* pSRVA = 0;
	ID3D11ShaderResourceView* pSRVB = 0;
	ID3D11UnorderedAccessView* pUAV = 0;

	m_pOwner->getDevice()->CreateShaderResourceView(m_pInputA, NULL, &pSRVA);
	m_pOwner->getDevice()->CreateShaderResourceView(m_pInputB, NULL, &pSRVB);
	m_pOwner->getDevice()->CreateUnorderedAccessView(m_pOutput, NULL, &pUAV);

	m_pOwner->getContext()->CSSetConstantBuffers(0, 1, &m_pCB);
	m_pOwner->getContext()->CSSetUnorderedAccessViews(0, 1, &pUAV, NULL);
	m_pOwner->getContext()->CSSetShaderResources(0, 1, &pSRVA);
	m_pOwner->getContext()->CSSetShaderResources(1, 1, &pSRVB);//??
	m_pOwner->getContext()->CSSetShader(m_pCS, NULL, NULL);

	SAFE_RELEASE(pSRVA);
	SAFE_RELEASE(pSRVB);
	SAFE_RELEASE(pUAV);
}

void CCSALU::execute(){
	D3D11_TEXTURE2D_DESC dtd;
	m_pOutput->GetDesc(&dtd);
	m_pOwner->getContext()->Dispatch(((dtd.Width + 7) / 8), ((dtd.Height + 7) / 8), 1);
	m_pOwner->getContext()->Flush();
	m_pOwner->getContext()->ClearState();
}

void CCSALU::unitialize(){
	SAFE_RELEASE(m_pCS);
	SAFE_RELEASE(m_pCB);
}

CCSALU::~CCSALU()
{
}
