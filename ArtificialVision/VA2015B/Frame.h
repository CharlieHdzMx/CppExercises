#pragma once
#include <Windows.h>

class CFrame
{
public:
	CFrame();
	~CFrame();
	CFrame(int sx, int sy);
	CFrame(CFrame& Frame);

	struct PIXEL{
		unsigned char r, g, b, a;
	};

	int m_sx;
	int m_sy;
	PIXEL& getPixel(int i, int j);
	void draw(HDC hdc, int x, int y);
protected:
	PIXEL* m_pFrame;
};

