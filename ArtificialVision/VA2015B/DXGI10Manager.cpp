#include "stdafx.h"
#include "DXGI10Manager.h"
#include <fstream>
using namespace std;

//Inicializamos los recursos que usaremos en el procesamiento de imagenes
DXGI10Manager::DXGI10Manager()
{
	m_pDevice = 0;
	m_pSwapChain = 0;
	m_pBackBuffer = 0;
}

//Enlistar el hardware que podemos usar para los procesos
IDXGIAdapter* DXGI10Manager::EnumDevices(HWND hWnd){
	IDXGIAdapter* pAdapter = 0;
	IDXGIFactory* pFactory = 0;

	HRESULT hr = CreateDXGIFactory(IID_IDXGIFactory, (void**)&pFactory);

	if (FAILED(hr))
		return 0;
	int iAdapter = 0;

	while (1){
		//Liberar adaptador anterior
		SAFE_RELEASE(pAdapter);

		hr=pFactory->EnumAdapters(iAdapter,&pAdapter);
		if (FAILED(hr))
			break;

		//Obtener Descripcion del Adaptador
		TCHAR szMessage[1024];
		DXGI_ADAPTER_DESC dad;
		pAdapter->GetDesc(&dad);

		wsprintf(szMessage, L"Description %s \r \n Video Memory: %d MB \r\n Shared Memory: %d MB \r\n System Memory: %d MB", 
			dad.Description,
			dad.DedicatedVideoMemory / (1024 * 1024),
			dad.SharedSystemMemory / (1024 * 1024),
			dad.DedicatedSystemMemory / (1024 * 1024));

		switch (MessageBox(hWnd, szMessage, L"Do you wish to use this device?", MB_ICONQUESTION | MB_YESNOCANCEL)){
		case IDYES:
			SAFE_RELEASE(pFactory);
			return pAdapter;

		case IDNO:
			break;

		case IDCANCEL:
			SAFE_RELEASE(pFactory);
			SAFE_RELEASE(pAdapter);
			return NULL;
		}
		iAdapter++;
	}
	SAFE_RELEASE(pFactory);
	return NULL;
}

bool DXGI10Manager::Initialize(HWND hWnd, IDXGIAdapter* pAdapter){
	HRESULT hr = E_FAIL;
	//Inicializacion de la descricion del swapchain.
	D3D_FEATURE_LEVEL FeatureLevel = D3D_FEATURE_LEVEL_10_0;
	DXGI_SWAP_CHAIN_DESC dscd;
	memset(&dscd, 0, sizeof(dscd));
	dscd.BufferCount = 2; dscd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dscd.BufferDesc.RefreshRate.Numerator = 0; dscd.BufferDesc.RefreshRate.Denominator = 0;
	dscd.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED; dscd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;

	//Obtener tamaño del monitor.
	RECT rc;
	GetClientRect(hWnd, &rc);
	dscd.BufferDesc.Height = rc.bottom; dscd.BufferDesc.Width = rc.right;

	dscd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_UNORDERED_ACCESS;
	dscd.OutputWindow = hWnd; dscd.Windowed = true;//No full screen en debug.
	dscd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;//De full screen a windowed.
	dscd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;//Descartar el front buffer anterior para eficiencia computacional.
	dscd.SampleDesc.Count = 1;//Antialiasing 
	dscd.SampleDesc.Quality = 0;//Calidad estandar sin sujecion de fabricante

	if (pAdapter){
		hr = D3D10CreateDeviceAndSwapChain(pAdapter, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
			D3D10_SDK_VERSION, &dscd, &m_pSwapChain, &m_pDevice);
		if (FAILED(hr))
			return false;
	}
	else{ 
		hr = D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_WARP, NULL, 0,
			D3D10_SDK_VERSION, &dscd, &m_pSwapChain, &m_pDevice);
		if (FAILED(hr))
			return false;
	}
	return true;
}

ID3D10Texture2D* DXGI10Manager::LoadImageFromFile(char* pszFileName){
	return NULL;
}

void DXGI10Manager::Uninitialize(void){
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pBackBuffer);
}

DXGI10Manager::~DXGI10Manager()
{
	Uninitialize();
}
