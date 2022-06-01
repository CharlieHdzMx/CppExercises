// VA2015B.cpp : Defines the// VA2015B.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "VA2015B.h"
#include "DXGIManager.h"
#include "DXGI10Manager.h"
#include "CSDefault.h"
#include "matrix.h"
#include "CSConvolution.h"
#include "CSALU.h"
#include "../Video/AtWareVideoCapture.h"
#include "VideoProcessor.h"
#include "SerialClass.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
CDXGIManager g_Manager;							//!!
ID3D11Texture2D* g_pSource;						//Source Image
ID3D11Texture2D* g_pSourceA;
ID3D11Texture2D* g_pSourceB;
ID3D11Texture2D* g_pSourceFrame;
CCSDefault g_Default(&g_Manager);
CCSConvolution g_Convolution(&g_Manager);
CCSALU g_ALU(&g_Manager);
IAtWareVideoCapture* g_pVC;						//The capture facade.
CVideoProcessor g_VP;


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI VideoWindowsProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_VA2015B, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VA2015B));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VA2015B));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_VA2015B);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}
	//Retorna adaptador
	//auto x=g_Manager.EnumDevices(hWnd);
	//if (!x)return FALSE;
	if (!g_Manager.Initialize(hWnd, NULL))
		return FALSE;
	g_Default.initialize();
	g_Convolution.initialize();
	g_ALU.initialize();

	g_pSourceA = g_Manager.LoadImageFromFile("..\\Resources\\star.bmp");
	g_pSourceB = g_Manager.LoadImageFromFile("..\\Resources\\adventure.bmp");
	g_pSource = g_Manager.LoadImageFromFile("..\\Resources\\adventure.bmp");

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	WNDCLASSEX wnc;
	memset(&wnc, 0, sizeof(wnc));
	wnc.cbSize = sizeof(WNDCLASSEX);
	wnc.hInstance = hInstance;
	wnc.lpszClassName = L"VideoWindow";
	wnc.style = CS_HREDRAW | CS_VREDRAW;
	wnc.lpfnWndProc = VideoWindowsProc;

	RegisterClassEx(&wnc);
	HWND hWndVideo = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"VideoWindow", L"Vista Previa", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	g_pVC = CreateAtWareVideoCapture();
	g_pVC->Initialize(hWndVideo);
	g_pVC->EnumAndChooseCaptureDevice();
	g_pVC->BuildStreamGraph();
	g_pVC->GetMediaType(&g_VP.m_mt);
	g_pVC->ShowPreviewWindow(true);
	g_pVC->SetCallBack(&g_VP, 1);
	g_pVC->Start();

	ShowWindow(hWndVideo, SW_MAXIMIZE);
	return TRUE;
}


vector<int> getGreyPixels(CFrame* frame){
	vector <int> lstPosition;
	lstPosition.clear();
	int lastY = 0;

	for (unsigned int i = 0; i < frame->m_sx; i++){
		for (unsigned int j = 0; j < frame->m_sy; j++){
			CFrame::PIXEL currentPixel = frame->getPixel(i, j);
			if (currentPixel.r <50 && currentPixel.g<50 && currentPixel.b <50)
			if (!i == 0 && i != lastY){
				lstPosition.push_back(i);
				lastY = i;
			}
		}
	}
	return lstPosition;
}

int locationAverage(vector<int> positions){
	unsigned long long acum = 0;

	if (positions.empty())
		return 0;

	for each (int value in positions)
	{
		acum += value;
	}

	return acum / positions.size();

}


int locationMid(vector<int> positions){
	if (positions.empty())
		return 0;
	return ((positions.back() - positions.front()) / 2) + positions.front();
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static int mx, my;//Coordenadas de mouse.
	static float theta;
	static float scale = 1.0f;
	static unsigned int choice = 0;
	static float x = 0.5f;
	static bool getFrame = 0;
	static CFrame* pFrame;
	static int prom = 0;
	static vector<int> vctPosition;
	static TCHAR buf[100];
	static bool start = false;
	UINT_PTR timer;

	switch (message)
	{
	case WM_MOUSEMOVE:
	{
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
	}
		break;
	case WM_KEYDOWN:
		switch (wParam){
		case 'G':
			start = true;
			break;
		}
		break;
	case WM_CREATE:
		SetTimer(hWnd, 1, 500, NULL);
		SetTimer(hWnd, 2, 8100, NULL);
		return 0;

	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			break;
		case 2:
			start = true;
			if (start){
				_stprintf_s(buf, _T("%d"), prom);
				if (prom < 214)
				{
					Serial* Arduino = new Serial("COM7");
					char palabra[] = "a";
					Arduino->WriteData(palabra, sizeof(palabra)-1);
					MessageBox(NULL, L"Esta en el primer bloque", buf, NULL);
					delete Arduino;
				}

				else if (prom < 214 * 2 && prom > 214)
				{
					Serial* Arduino = new Serial("COM7");
					char palabra[] = "b";
					Arduino->WriteData(palabra, sizeof(palabra)-1);
					MessageBox(NULL, L"Esta en el segundo bloque", buf, NULL);
					delete Arduino;
				}
				else
				{
					Serial* Arduino = new Serial("COM7");
					char palabra[] = "c";
					Arduino->WriteData(palabra, sizeof(palabra)-1);
					MessageBox(NULL, L"Esta en el tercer bloque", buf, NULL);
					delete Arduino;
				}
				start=false;
			}
		}
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_SIZE:
		if (g_Manager.getDevice())
			g_Manager.resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
					 ID3D11Texture2D* VideoInput = NULL;

					 D3D11_TEXTURE2D_DESC dtd;
					 g_pSource->GetDesc(&dtd);
					 g_Manager.getDevice()->CreateTexture2D(&dtd, NULL, &VideoInput);

					 CFrame *Frame = g_VP.Pull();
					 if (Frame != NULL)
						 VideoInput = g_Manager.LoadImageFromFrame(Frame);

					 if (g_Manager.getDevice())
					 {

						 g_ALU.m_pInputA = VideoInput;
						 g_ALU.m_pInputB = g_pSource;
						 g_ALU.m_pOutput = g_Manager.getBackBuffer();
						 g_ALU.m_Params.option = 0;
						 g_ALU.configure();
						 g_ALU.execute();
						 g_Manager.getSwapChain()->Present(2, 0);

						 if (Frame != NULL)
						 {
							 vctPosition = getGreyPixels(Frame);
							 prom = locationMid(vctPosition);
						 }

						 delete Frame;
						 SAFE_RELEASE(VideoInput);
					 }
					 ValidateRect(hWnd, NULL);
					 break;
	}
	case WM_DESTROY:
		pFrame->~CFrame();
		PostQuitMessage(0);
		KillTimer(hWnd, 1);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT WINAPI VideoWindowsProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg){
	case WM_SIZE:
		if (g_pVC){
			RECT rc;
			GetClientRect(hWnd, &rc);
			g_pVC->SetPreviewWindowPosition(&rc);
		}
		break;
	case WM_CLOSE:
		return 0;
	case WM_CREATE:
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}