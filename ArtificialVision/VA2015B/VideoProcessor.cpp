#include "stdafx.h"
#include "VideoProcessor.h"


CVideoProcessor::CVideoProcessor()
{
	InitializeCriticalSection(&m_csLock);
}


CVideoProcessor::~CVideoProcessor()
{
	DeleteCriticalSection(&m_csLock);
}

void CVideoProcessor::Push(CFrame* pFrame){
	EnterCriticalSection(&m_csLock);
	//1 core process
	if (m_lstFrame.size() > 60){
		CFrame* pFrameToDestroy = m_lstFrame.front();
		m_lstFrame.pop_front();
		delete pFrameToDestroy;
	}
	m_lstFrame.push_back(pFrame);
	LeaveCriticalSection(&m_csLock);
}

CFrame* CVideoProcessor::Pull(){

	CFrame* pFrame = NULL;
	EnterCriticalSection(&m_csLock);
	if (m_lstFrame.size()){
		pFrame = m_lstFrame.front();
		m_lstFrame.pop_front();
	}
	LeaveCriticalSection(&m_csLock);
	return pFrame;
}

HRESULT CVideoProcessor::SampleCB(double SampleTime, IMediaSample* pSample){
	return S_OK;
}

int Clear(int value){
	if (value > 255){
		return 255;
	}
	else if (value <= 0){
		return 0;
	}
	else{
		return value;
	}

}

HRESULT CVideoProcessor::BufferCB(double SampleTime, BYTE* pBuffer, long BufferLen){

	if (MEDIATYPE_Video == m_mt.majortype){
		//YUY2

		VIDEOINFOHEADER* pVIH = (VIDEOINFOHEADER*)m_mt.pbFormat;
		CFrame* pF = new CFrame(pVIH->bmiHeader.biWidth, pVIH->bmiHeader.biHeight);

		if (MEDIASUBTYPE_YUY2 == m_mt.subtype){
			//Analisis del header 
			struct YUY2{
				unsigned char y0, u0, y1, v0;
			};

			//Se analiza el frame byte por byte
			for (int j = 0; j < pVIH->bmiHeader.biHeight; j++){

				YUY2* pRow = (YUY2*)(pBuffer + j*pVIH->bmiHeader.biWidth *2);

				for (int i = 0; i < pVIH->bmiHeader.biWidth / 2; i++){
					CFrame::PIXEL currentPixel;
					int C1 = pRow->y0 ;
					int C2 = pRow->y1 ;
					int D = pRow->u0 - 128;
					int E = pRow->v0 - 128;

					currentPixel.r = Clear(C1 + 1.13983*D);
					currentPixel.g = Clear(C1 - 0.39465*D- 0.58060*E);
					currentPixel.b = Clear(C1 + 2.03211*E);
					pF->getPixel(i * 2, j) = currentPixel;

					currentPixel.r = Clear(C2 + 1.13983*D);
					currentPixel.g = Clear(C2 - 0.39465*D - 0.58060*E);
					currentPixel.b = Clear(C2 + 2.03211*E);
					pF->getPixel(i * 2 + 1, j) = currentPixel;
					pRow++;
				}
			}
		}

		else if (MEDIASUBTYPE_RGB24 == m_mt.subtype){

			for (int j = 0; j < pVIH->bmiHeader.biHeight; j++){
				RGBTRIPLE* pRow = (RGBTRIPLE*)(pBuffer + j*pVIH->bmiHeader.biWidth*3);
				for (int i = 0; i < pVIH->bmiHeader.biWidth; i++){					
					CFrame::PIXEL currentPixel;
					currentPixel.r = pRow->rgbtRed;
					currentPixel.g = pRow->rgbtGreen;
					currentPixel.b = pRow->rgbtBlue;
					currentPixel.a = NULL;
					pF->getPixel(i, j) = currentPixel;
					pRow++;
				}
			}			
		}

		Push(pF);
	}
	return S_OK;
}
