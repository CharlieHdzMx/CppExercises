#pragma once
#include "GraphManager.h"
#include <Windows.h>


class CEdge
{
	friend class CGraphManager;

	CGraphManager* m_pGraphManager;

public:

	unsigned long getKeyEdge()const;

	virtual void DrawEdge(HDC hdc);

protected:
	
	union
	{
		struct
		{
			unsigned long m_ulIDFirst;
			unsigned long m_ulIDSecond;
		};

		unsigned long long m_ullID;
	};

	CEdge();
	virtual ~CEdge();
};

