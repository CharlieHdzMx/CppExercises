#pragma once
#include "..\Video\AtWareVideoCapture.h"
#include "Frame.h"
#include <list>
#include <Windows.h>

using namespace std;

class CVideoProcessor :
	public IAtWareSampleGrabberCB
{
public:
	CVideoProcessor();
	~CVideoProcessor();
	void Push(CFrame* pFrame);
	CFrame* Pull();
	AM_MEDIA_TYPE m_mt; //Media type info (Video Format).


protected:
	HRESULT SampleCB(double SampleTime, IMediaSample *pSample);
	HRESULT BufferCB(double SampleTime, BYTE *pBuffer, long BufferLen);

	list<CFrame*> m_lstFrame;
	CRITICAL_SECTION m_csLock;
};

