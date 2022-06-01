#pragma once
#include <d3d10.h>
#include <dxgi.h>

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(X){if((X)){(X)->Release(); (X)=0;}}
#endif

class DXGI10Manager
{
protected:
	ID3D10Device* m_pDevice;
	IDXGISwapChain* m_pSwapChain;
	ID3D10Texture2D* m_pBackBuffer;

public:
	ID3D10Device* getDevice(){ return m_pDevice; }
	IDXGISwapChain* getSwapChain(){ return m_pSwapChain; }
	ID3D10Texture2D* getBackBuffer(){ return m_pBackBuffer; }
	struct PIXEL{ //DXGI_FORMAT_R8G8B8A8_XXXXX
		unsigned char r, g, b, a;
	};

	bool Initialize(HWND hWnd, IDXGIAdapter* pAdapter);
	void Uninitialize(void);
	IDXGIAdapter* EnumDevices(HWND hWnd);
	ID3D10Texture2D* LoadImageFromFile(char* pszFileName);

	DXGI10Manager();
	~DXGI10Manager();
};

