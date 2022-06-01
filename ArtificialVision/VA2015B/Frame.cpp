#include "stdafx.h"
#include "Frame.h"



CFrame::CFrame()
{
}

CFrame::CFrame(int sx, int sy){
	m_pFrame = new PIXEL[sx*sy];
	m_sx = sx;
	m_sy = sy;
}

CFrame::CFrame(CFrame& Frame):CFrame(Frame.m_sx,Frame.m_sy){
	memcpy(m_pFrame, Frame.m_pFrame, sizeof(PIXEL)*m_sx*m_sy);	
}

CFrame::~CFrame()
{
	delete[] m_pFrame;
}

CFrame::PIXEL& CFrame::getPixel(int i, int j){
	static PIXEL Dummy;
	if (i >= 0 && i < m_sx && j >= 0 && j < m_sy)
		return m_pFrame[(m_sx*j) + i];
	return Dummy;
}

void CFrame::draw(HDC hdc, int sx, int sy){
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmp = CreateCompatibleBitmap(hdc, m_sx, m_sy);
	SelectObject(hdcMem, hbmp);
	SetBitmapBits(hbmp, m_sx*m_sy*sizeof(PIXEL), m_pFrame);
	BitBlt(hdc, sx, sy, m_sx, m_sy, hdcMem, 0, 0, SRCCOPY);
	DeleteObject(hbmp);
	DeleteDC(hdcMem);
}
