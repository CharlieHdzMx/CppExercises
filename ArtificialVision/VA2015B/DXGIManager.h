#pragma once
#include <d3d11.h>
#include <d3d10.h>
#include <dxgi.h>


#ifndef SAFE_RELEASE
	#define SAFE_RELEASE(X) {if((X)){(X)->Release(); (X)=0;}}
#endif

class CFrame;

class CDXGIManager
{
protected:
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pContext; //Execution Queue Hardware Context.
	IDXGISwapChain* m_pSwapChain; //Hardware Flipping for 2 or more buffers
	ID3D11Texture2D* m_BackBuffer; //Back Buffer Image in swap chain


public:
	ID3D11Device* getDevice(){ return m_pDevice; }
	ID3D11DeviceContext* getContext(){ return m_pContext; }
	IDXGISwapChain* getSwapChain(){ return m_pSwapChain; }
	ID3D11Texture2D* getBackBuffer(){ return m_BackBuffer; }
	
	struct PIXEL{ //DXGI_FORMAT_R8G8B8A8_XXXXX
		unsigned char r, g, b, a;
	};

	bool Initialize(HWND hWnd, IDXGIAdapter* pAdapter);
	void Uninitialize(void);
	IDXGIAdapter* EnumDevices(HWND hWnd);
	ID3D11Texture2D* LoadImageFromFile(char* pszFileName);
	ID3D11Texture2D* LoadImageFromFrame(CFrame* pFrame);
	ID3D11ComputeShader* CompileCS(wchar_t* pszFile , char* pszEntryPoint); 
	void resize(int sx, int sy);

	CDXGIManager();
	~CDXGIManager();
};

