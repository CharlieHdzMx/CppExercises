#include "stdafx.h"
#include "Vertex.h"
#include <ctype.h>
#include <stdlib.h>


CVertex::CVertex()
{
}


CVertex::~CVertex()
{
}

void CVertex::DrawVertex(HDC hdc){

	Ellipse(hdc, -15 + m_fx, -15 + m_fy, 15 + m_fx, 15 + m_fy);
	char szKey[32], *pszKey; 
	_itoa_s(m_ulID, szKey, 10);
	TextOutA(hdc, m_fx - 3, m_fy - 7, szKey, strlen(szKey));
}



unsigned long CVertex::GetKey()const
{
	return m_ulID;
}




bool CVertex::HitTest(short s_CoordX, short s_CoordY)
{
	if (s_CoordX > (m_fx - 15) && s_CoordX < (m_fx + 15) && s_CoordY >(m_fy - 15) && s_CoordY < (m_fy+15))
		return true;
	else
		return false;
}

void CVertex::setVertexID(unsigned long ulID){

	m_ulID = ulID;
}