
#include "stdafx.h"
#include "DXGIManager.h"
#include <fstream>
#include <d3dcompiler.h>
#include "Frame.h"

using namespace std;

CDXGIManager::CDXGIManager()
{
	m_pDevice = 0;
	m_pContext = 0;
	m_pSwapChain = 0;
	m_BackBuffer = 0;
}


IDXGIAdapter* CDXGIManager::EnumDevices(HWND hWnd){
	IDXGIAdapter* pAdapter = 0;
	IDXGIFactory* pFactory = 0;
	HRESULT hr=
	CreateDXGIFactory(IID_IDXGIFactory, (void**) &pFactory);
	if (FAILED(hr))
		return 0;

	int iAdapter = 0;
	while (1){
		SAFE_RELEASE(pAdapter);
		hr=pFactory->EnumAdapters(iAdapter, &pAdapter);

		if (FAILED(hr))
			break;
		TCHAR szMessage[1024];
		DXGI_ADAPTER_DESC dad;
		pAdapter->GetDesc(&dad);
		wsprintf(szMessage, L"Description: %s \r\n  Video Memory:%d MB \r\n Shared Memory: %d MB \r\n System Memory: \r\n %d MB",
			dad.Description, dad.DedicatedVideoMemory / (1024 * 1024),
			dad.SharedSystemMemory / (1024 * 1024), dad.DedicatedSystemMemory/ (1024 * 1024));

		switch (MessageBox(hWnd, szMessage, 
			L"Do you wish to use this device?", 
			MB_ICONQUESTION | MB_YESNOCANCEL)){

		case IDYES:
			SAFE_RELEASE(pFactory);
			return pAdapter;

		case IDNO:
			break;

		case IDCANCEL:
			SAFE_RELEASE(pFactory);
			SAFE_RELEASE(pAdapter);
			return 0;
		}
		iAdapter++;
	}	
	SAFE_RELEASE(pFactory);

	return 0;
}



void CDXGIManager::Uninitialize(void){
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pContext);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_BackBuffer);
}

bool CDXGIManager::Initialize(HWND hwnd, IDXGIAdapter* pAdapter){
	HRESULT hr = E_FAIL;

	D3D_FEATURE_LEVEL FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL DetectedFeatureLevel;
	//Solicitar cadena de intercambio
	DXGI_SWAP_CHAIN_DESC dscd;
	memset(&dscd, 0, sizeof(dscd));
	dscd.BufferCount = 2;
	dscd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Unknow Norm de 0 a 1.
	dscd.BufferDesc.RefreshRate.Numerator = 0;
	dscd.BufferDesc.RefreshRate.Denominator = 0;
	dscd.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
	dscd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	//Tamaño del monitor
	RECT rc;
	GetClientRect(hwnd, &rc);
	dscd.BufferDesc.Height = rc.bottom;
	dscd.BufferDesc.Width = rc.right;

	dscd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_UNORDERED_ACCESS;
	dscd.OutputWindow = hwnd;
	dscd.Windowed = true; //Al depurar no utilizar full screen, osea windowed=false;
	dscd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //Permite el cambio de full screen a windowed
	dscd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //Descartar el front buffer anterior
	dscd.SampleDesc.Count = 1; //Antialiasing de varios pixeles en uno solo.
	dscd.SampleDesc.Quality = 0;//Calidad estandar sin sujecion de fabricante.


	if (pAdapter){//Se ha seleccionado un adaptador especifico.
		hr = D3D11CreateDeviceAndSwapChain(pAdapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, 0, &FeatureLevel,
		1, D3D11_SDK_VERSION, &dscd, &m_pSwapChain, &m_pDevice, &DetectedFeatureLevel, &m_pContext);
		if (FAILED(hr))
			return false;
	}
	else{//Se ha optado por seleccionar el adaptador primario

		hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_WARP, NULL, 0,
			&FeatureLevel, 1, D3D11_SDK_VERSION, &dscd, &m_pSwapChain, &m_pDevice, &DetectedFeatureLevel, &m_pContext);

		if (FAILED(hr))
			return false;
	}
	resize(rc.right, rc.bottom);
	return true;
}

ID3D11Texture2D* CDXGIManager::LoadImageFromFrame(CFrame* pFrame){
	D3D11_TEXTURE2D_DESC dtd;
	memset(&dtd, 0, sizeof(dtd));
	dtd.Width = pFrame->m_sx;
	dtd.Height = pFrame->m_sy;
	dtd.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Decidir en que lo vamos a implementar
	dtd.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
	dtd.Usage = D3D11_USAGE_STAGING;
	dtd.ArraySize = 1;
	dtd.MipLevels = 1;
	dtd.SampleDesc.Count = 1;
	dtd.SampleDesc.Quality = 0;

	ID3D11Texture2D* pStaging=NULL;

	m_pDevice->CreateTexture2D(&dtd, 0, &pStaging);
	D3D11_MAPPED_SUBRESOURCE ms;
	m_pContext->Map(pStaging, 0, D3D11_MAP_WRITE, 0, &ms);

	char* pStagingBuffer = (char*)ms.pData; //Aritmetica de Byte para brincar de pitch a pitch
	for (int j = 0; j < pFrame->m_sy; j++){
		memcpy(pStagingBuffer,
			&pFrame->getPixel(0, j),
			sizeof(CFrame::PIXEL)*pFrame->m_sx);
		pStagingBuffer += ms.RowPitch;
	}
	m_pContext->Unmap(pStaging, 0);

	ID3D11Texture2D* pTexture=NULL;
	dtd.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	dtd.CPUAccessFlags = 0;
	dtd.Usage = D3D11_USAGE_DEFAULT;
	m_pDevice->CreateTexture2D(&dtd, 0, &pTexture);
	m_pContext->CopyResource(pTexture, pStaging);
	SAFE_RELEASE(pStaging);

	return pTexture;
	
}

ID3D11Texture2D* CDXGIManager::LoadImageFromFile(char* pszFileName){

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	fstream in;
	in.open(pszFileName, ios::in | ios::binary);
	if (!in.is_open())
		return NULL;

	//Header archivo.
	in.read((char*)&bfh.bfType, sizeof(bfh.bfType)); //Lectura de tipo.
	if ('MB' != bfh.bfType)
		return NULL;
	in.read((char*)&bfh.bfSize, sizeof(bfh)-sizeof(bfh.bfType));//Leer resto

	//Informacion del bitmap.
	in.read((char*)&bih.biSize, sizeof(bih.biSize));//Firma electronica por tamaño
	if (sizeof(bih) != bih.biSize)
		return NULL;
	in.read((char*)&bih.biWidth, sizeof(bih)-sizeof(bih.biSize));//Resto

	D3D11_TEXTURE2D_DESC dtd;
	memset(&dtd, 0, sizeof(dtd));
	dtd.ArraySize = 1; //las imagenes que estamos cargando
	dtd.BindFlags = 0;//No se atan a ningun hardware de GPU.
	dtd.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;//Como usar la ventana de acceso
	dtd.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Formato de Pixel de la textura.
	dtd.Height = bih.biHeight;
	dtd.Width = bih.biWidth;
	dtd.MipLevels = 1;
	dtd.SampleDesc.Count = 1;
	dtd.SampleDesc.Quality = 0;
	dtd.Usage = D3D11_USAGE_STAGING;
	ID3D11Texture2D* pStaging=0;
	HRESULT hr=m_pDevice->CreateTexture2D(&dtd, NULL, &pStaging);//Crear andamio
	if (FAILED(hr))
		return NULL;


	switch (bih.biBitCount)
	{
	case 1://1 bit p/pxl
	{
			   RGBQUAD paleta[2];
			   int nColors = bih.biClrUsed == 0 ? 1 : bih.biClrUsed;
			   in.read((char*)paleta, sizeof(paleta)*nColors);
			   int rowLength = 4* ((bih.biBitCount*bih.biWidth + 31) / 32);
			   unsigned char* pRow = new unsigned char[rowLength];
			   D3D11_MAPPED_SUBRESOURCE ms;
			   m_pContext->Map(pStaging, 0, D3D11_MAP_READ_WRITE, 0, &ms);
			   PIXEL* pLine; //32 bits

			   //Por cada y fila
			   for (int j = bih.biHeight - 1; j >= 0; j--){
				   in.read((char*)pRow, rowLength); //!
				   pLine = (PIXEL*)((char*)ms.pData + ms.RowPitch*j);
				   unsigned int indice = 0;

				   for (int i = 0; i < rowLength; i++){
					   unsigned char pixelsByte = pRow[i];
					   unsigned char mask = 128;
					   for (unsigned int k = 7; k > 0; k--){
						   unsigned char pixel = pixelsByte&mask;
						   pixel = pixel >> k;
						   RGBQUAD Cs = paleta[pixel];
						   PIXEL Cd;
						   Cd.r = Cs.rgbRed;
						   Cd.g = Cs.rgbGreen;
						   Cd.b = Cs.rgbBlue;
						   Cd.a = 0xff;
						   mask /= 2;
						   pLine[indice] = Cd;
						   indice++;
					   }
					   //end k
				   }
			   }
			   m_pContext->Unmap(pStaging, 0);
			   delete[] pRow;
	}
		break;
	case 4://4 bit p/pxl.
	{	   
			   RGBQUAD paleta[16];
			   
			   int nColors = bih.biClrUsed == 0 ? 16 : bih.biClrUsed;
			   in.read((char*)paleta, sizeof(RGBQUAD)*nColors);
			   int rowLength = 4 * ((bih.biBitCount*bih.biWidth + 31) / 32);
			   unsigned char* pRow = new unsigned char[rowLength];
			   D3D11_MAPPED_SUBRESOURCE ms;
			   m_pContext->Map(pStaging, 0, D3D11_MAP_READ_WRITE, 0, &ms);
			   PIXEL* pLine; //32 bits
			   
			   //Por cada y fila
			   for (int j = bih.biHeight - 1; j >= 0; j--){
				   in.read((char*)pRow, rowLength); //!
				   pLine = (PIXEL*)((char*)ms.pData + ms.RowPitch*j);
				   unsigned int indice = 0;

				   for (int i = 0; i < rowLength; i++){
					   unsigned char pixelsByte = pRow[i];
					   unsigned char mask = 240;
						unsigned char nibbles = (pixelsByte & mask)>>4;
						   RGBQUAD Cs = paleta[nibbles];
						   PIXEL Cd;
						   Cd.r = Cs.rgbRed;
						   Cd.g = Cs.rgbGreen;
						   Cd.b = Cs.rgbBlue;
						   Cd.a = 0xff;
						   pLine[indice] = Cd;

						   mask =mask>>4;
						   nibbles = (pixelsByte&mask);
						   Cs = paleta[nibbles];
						   Cd.r = Cs.rgbRed;
						   Cd.g = Cs.rgbGreen;
						   Cd.b = Cs.rgbBlue;
						   Cd.a = 0xff;
						   pLine[indice+1] = Cd;
						   indice+=2;
					   //end k  
			   }
	}
			   m_pContext->Unmap(pStaging, 0);
			   delete[] pRow;
	}
		break;
	case 8://8 bit p/pxl.
	{
			   RGBQUAD paleta[256];
			   int nColors = bih.biClrUsed == 0 ? 256 : bih.biClrUsed;
			   in.read((char*)paleta, sizeof(RGBQUAD)*nColors);//Lectura.
			   int rowLength = 4*((bih.biBitCount*bih.biWidth + 31) / 32);//Tamaño de toma de datos.
			   unsigned char* pRow = new unsigned char[rowLength];
			   //Lectura de Linea por linea.
			   D3D11_MAPPED_SUBRESOURCE  ms;//Memoria de Kernel en memoria de usuario.
			   m_pContext->Map(pStaging, 0, D3D11_MAP_READ_WRITE, 0, &ms);
			   //Lectura de ixeles.
			   PIXEL *pLine;
			   //Uso de pixel
			   for (int j = bih.biHeight - 1; j >= 0; j--){

				   in.read((char*)pRow, rowLength);
				   pLine = (PIXEL*)((char*)ms.pData + ms.RowPitch*j);

				   for (int i = 0; i < bih.biWidth; i++){
					   PIXEL Cd; RGBQUAD Cs;

					   Cs = paleta[pRow[i]];
					   Cd.r = Cs.rgbRed;
					   Cd.g = Cs.rgbGreen;
					   Cd.b = Cs.rgbBlue;
					   Cd.a = 0xff;
					   pLine[i] = Cd;
				   }
			   }
			   m_pContext->Unmap(pStaging, 0);
			   delete[] pRow;
	}
		break;
	case 24:
	{
			   int rowLength = 4 * ((bih.biBitCount*bih.biWidth + 31) / 32);//Tamaño de toma de datos.
			   unsigned char* pRow = new unsigned char[rowLength];
			   //Lectura de Linea por linea.
			   D3D11_MAPPED_SUBRESOURCE  ms;//Memoria de Kernel en memoria de usuario.
			   m_pContext->Map(pStaging, 0, D3D11_MAP_READ_WRITE, 0, &ms);
			   //Lectura de ixeles.
			   PIXEL *pLine;
			   for (int j = bih.biHeight - 1; j >= 0; j--){

				   in.read((char*)pRow, rowLength);
				   pLine = (PIXEL*)((char*)ms.pData + ms.RowPitch*j);

				   for (int i = 0; i < bih.biWidth; i++){
					   PIXEL Cd;
					   Cd.b = pRow[(i*3)];
					   Cd.g = pRow[(i * 3) + 1];
					   Cd.r = pRow[(i * 3) + 2];
					   Cd.a = 0xff;
					   pLine[i] = Cd;
				   }
			   }
			   m_pContext->Unmap(pStaging, 0);
			   delete[] pRow;
	}
		break;
	case 32:
	{
			   int rowLength = 4 * ((bih.biBitCount*bih.biWidth + 31) / 32);//Tamaño de toma de datos.
			   unsigned char* pRow = new unsigned char[rowLength];
			   //Lectura de Linea por linea.
			   D3D11_MAPPED_SUBRESOURCE  ms;//Memoria de Kernel en memoria de usuario.
			   m_pContext->Map(pStaging, 0, D3D11_MAP_READ_WRITE, 0, &ms);
			   //Lectura de ixeles.
			   PIXEL *pLine;
			   for (int j = bih.biHeight - 1; j >= 0; j--){

				   in.read((char*)pRow, rowLength);
				   pLine = (PIXEL*)((char*)ms.pData + ms.RowPitch*j);

				   for (int i = 0; i < bih.biWidth; i++){
					   PIXEL Cd;
					   Cd.b = pRow[(i * 4)];
					   Cd.g = pRow[(i * 4) + 1];
					   Cd.r = pRow[(i * 4) + 2];
					   Cd.a = pRow[(i * 4) + 3];
					   pLine[i] = Cd;
				   }
			   }
			   m_pContext->Unmap(pStaging, 0);
			   delete[] pRow;
	}
		break;
	}

	dtd.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	dtd.CPUAccessFlags = 0;
	dtd.Usage = D3D11_USAGE_DEFAULT;
	ID3D11Texture2D* pTexture = 0;
	hr=m_pDevice->CreateTexture2D(&dtd, NULL, &pTexture);

	if (FAILED(hr)){
		SAFE_RELEASE(pStaging);
		return NULL;
	}

	m_pContext->CopyResource(pTexture, pStaging);
	SAFE_RELEASE(pStaging);
	return pTexture;
}

ID3D11ComputeShader* CDXGIManager::CompileCS(wchar_t* pszFileName, char* pszEntryPoint){

	//1.-Generacion del codigo intermedio. HLSL a  DXIL (Direct X Intermediate Language)
	//2.-Generacion de codigo nativo (DXIL ->Nvidia)

	ID3D10Blob* pDXIL;
	ID3D10Blob* pErrors;

#ifdef _DEBUG
	DWORD dwOption=D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_ENABLE_STRICTNESS;
#else
	DWORD dwOption = D3DCOMPILE_OPTIMIZATION_LEVEL3 | D3DCOMPILE_ENABLE_STRICTNESS;
#endif
	HRESULT hr=
		D3DCompileFromFile(pszFileName, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, pszEntryPoint, "cs_5_0", dwOption, 0, &pDXIL, &pErrors);

	if (pErrors){
		MessageBoxA(NULL, (char*)pErrors->GetBufferPointer(), "Errores", MB_ICONERROR);
		SAFE_RELEASE(pDXIL);
		SAFE_RELEASE(pErrors);
		return NULL;
	}
	if (FAILED(hr))
		return NULL;

	//2
	ID3D11ComputeShader* pCS = NULL;
	hr=m_pDevice->CreateComputeShader(pDXIL->GetBufferPointer(), pDXIL->GetBufferSize(), NULL, &pCS);
	
	SAFE_RELEASE(pDXIL);
	SAFE_RELEASE(pErrors);

	if (FAILED(hr))
		return NULL;
	return pCS;
}

void CDXGIManager::resize(int sx, int sy){
	if (m_pDevice){
		m_pContext->ClearState();//Pone en estado original el contexto.
		SAFE_RELEASE(m_BackBuffer);
		m_pSwapChain->ResizeBuffers(2, sx, sy, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		m_pSwapChain->GetBuffer(0, IID_ID3D11Texture2D,(void**)&m_BackBuffer);
	}
}


CDXGIManager::~CDXGIManager()
{
	Uninitialize();
}
