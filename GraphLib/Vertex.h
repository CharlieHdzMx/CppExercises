#pragma once
#include <Windows.h>
#include <fstream>

using namespace std;

class InvestChoiceEnviroment;

class CVertex
{
	friend class InvestChoiceEnviroment;

	friend class CGraphManager;

public:
	void setVertexID(unsigned long ulID);

	unsigned long GetKey()const;

	virtual void DrawVertex(HDC hdc);

	float m_fx, m_fy;

	float m_fh;

	unsigned long m_ulIDParent;

	bool m_bVisited ;

	bool HitTest(short s_CoordX, short s_CoordY);


	CVertex();

	virtual ~CVertex();

protected:

	CGraphManager* m_Manager;

	unsigned long m_ulID;

};

