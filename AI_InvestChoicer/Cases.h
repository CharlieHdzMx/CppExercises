#pragma once
#include "..\\GraphLib\\Vertex.h"
#include <list>
#include "ChoiceEvent.h"
#include <string>

using namespace std;

class CCases 
{
public:
	CVertex m_CaseVertex;

	CVertex* m_pCaseVertex;

	string Name;

	float m_fH;

	unsigned int Cost;

	unsigned int Promise;

	list<CChoiceEvent*> m_lChoiceEvents;

	CCases();
	virtual ~CCases();
	// Toma aleatoriamente un elemento de la lista de Eventos y lo retorna
	CChoiceEvent* PickRandomEvent();
};

