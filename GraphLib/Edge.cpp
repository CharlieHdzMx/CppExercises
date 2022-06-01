#include "stdafx.h"
#include "Edge.h"
#include "Vertex.h"


CEdge::CEdge()
{
}


CEdge::~CEdge()
{
}


unsigned long CEdge::getKeyEdge()const
{
	return m_ullID;
}

void CEdge::DrawEdge(HDC hdc){
	POINT a_triangulo[3];
	CVertex *pVFirst, *pVSecond;
	pVFirst = m_pGraphManager->CreateVertex(m_ulIDFirst);
	pVSecond = m_pGraphManager->CreateVertex(m_ulIDSecond);
	HBRUSH brocha;
	float m = 0;
	float x1 = pVFirst->m_fx;
	float y1 = pVFirst->m_fy;
	float x2 = pVSecond->m_fx;
	float y2 = pVSecond->m_fy;
	float l_y;
	float l_x;
	float f_y;
	float f_x;
	float f_tetha;
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	brocha = CreateSolidBrush(RGB(0, 0, 0));//brocha roja

	//Determinando el punto medio de la arista
	float i_medx = (x1 + x2) / 2;
	float i_medy = (y1 + y2) / 2;

	//Para líneas con pendiente 0
	if (y1 == y2)
	{
		a_triangulo[0].x = i_medx;
		a_triangulo[0].y = i_medy + 5;

		a_triangulo[1].x = i_medx;
		a_triangulo[1].y = i_medy - 5;

		if (pVFirst->m_fx < pVSecond->m_fx)//Dirección de la flecha
		{
			a_triangulo[2].x = i_medx + 10;
		}
		if (pVFirst->m_fx >pVSecond->m_fy)//Dirección de la fleca
		{
			a_triangulo[2].x = i_medx - 10;
		}

		a_triangulo[2].y = i_medy;
		SelectObject(hdc, brocha);
		Polygon(hdc, a_triangulo, 3);
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		DeleteObject(brocha);

	}
	//Para líneas con pendiente 0

	//Para líneas con pendiente -> inf
	if (x1 == x2)
	{
		a_triangulo[0].x = i_medx + 5;
		a_triangulo[0].y = i_medy;

		a_triangulo[1].x = i_medx - 5;
		a_triangulo[1].y = i_medy;

		a_triangulo[2].x = i_medx;

		if (pVFirst->m_fy < pVSecond->m_fy)//Dirección de la flecha
		{
			a_triangulo[2].y = i_medy + 10;
		}
		if (pVFirst->m_fy > pVSecond->m_fy)//Dirección de la flecha
		{
			a_triangulo[2].y = i_medy - 10;
		}
		SelectObject(hdc, brocha);
		Polygon(hdc, a_triangulo, 3);
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		DeleteObject(brocha);
	}
	//Para líneas con pendiente -> inf

	//Para líneas con pendiente determinada 
	if (y1 != y2 && x2 != x1)
	{

		//BASE
		m = (y2 - y1) / (x2 - x1);
		m = -(1 / m);

		//Sacando un punto con direccion perpendicular al centro de la línea
		l_x = i_medx + 20;
		l_y = m*(l_x - i_medx) + i_medy;
		//Sacando un punto con direccion perpendicular al centro de la línea


		f_x = (l_x - i_medx);
		f_y = (l_y - i_medy);
		f_tetha = atan(f_y / f_x);
		//Se saca el angulo para sacar una línea con misma direccion al punto
		//previamente calculado con direccion perpendicular al trazo, sin embargo
		//se requiere que este sea de una magnitud especifica, en este caso 13
		a_triangulo[1].x = (cos(f_tetha) * 5) + i_medx;
		a_triangulo[1].y = (sin(f_tetha) * 5) + i_medy;

		//Sacando un punto con direccion perpendicular al centro de la línea
		l_x = i_medx + 20;
		l_y = m*(l_x - i_medx) + i_medy;
		//Sacando un punto con direccion perpendicular al centro de la línea

		f_x = (l_x - i_medx);
		f_y = (l_y - i_medy);
		f_tetha = -3.141621 + atan(f_y / f_x); //Angulo desfazado 180 grados con respecto al primero

		a_triangulo[0].x = (cos(f_tetha) * 5) + i_medx;
		a_triangulo[0].y = (sin(f_tetha) * 5) + i_medy;
		//BASE

		//PUNTA
		f_x = (x2 - i_medx);
		f_y = (y2 - i_medy);
		if (x1 > x2);//Cuando punto incial a la derecha de punto final
		{
			f_tetha = -3.141621 + atan(f_y / f_x);//desfaze de 180 grados 
		}
		if (x1 < x2)//Cuando punto incial a la izquiera de punto final
		{
			f_tetha = atan(f_y / f_x);
		}
		a_triangulo[2].x = (cos(f_tetha) * 10) + i_medx;
		a_triangulo[2].y = (sin(f_tetha) * 10) + i_medy;
		//PUNTA
		SelectObject(hdc, brocha);
		Polygon(hdc, a_triangulo, 3);
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		DeleteObject(brocha);
	}
	
}
