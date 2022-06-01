#include "stdafx.h"
#include "Cases.h"
#include <iostream>
#include <cstdlib>
#include <ctime>



CCases::CCases(){

	m_pCaseVertex = &m_CaseVertex;
}


CCases::~CCases()
{
}


// Toma aleatoriamente un elemento de la lista de Eventos y lo retorna
CChoiceEvent* CCases::PickRandomEvent()
{
	unsigned int count;
	unsigned int random_integer;

	while (1)
	{
		count = 0;
		random_integer = rand() % 5;

		for (auto it = m_lChoiceEvents.begin(); it != m_lChoiceEvents.end(); it++)
		{
			CChoiceEvent* PickedEvent = *it;

			if (random_integer == count)
				return PickedEvent;

			count++;
		}
	}
}
