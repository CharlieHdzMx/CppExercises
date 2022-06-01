#include "stdafx.h"
#include "ClimbToHillBot.h"
#include <map>

using namespace std;

CClimbToHillBot::CClimbToHillBot()
{
}


CClimbToHillBot::~CClimbToHillBot()
{
}


// Especializacion del interfaz de SelectCase que toma en cuenta la heuristica y el costo.Este implementa un contenedor multimap para poder ordenar los casos por su heuristica-costo y despues  de esto tomar el de mayor diferencia promesa.costo
CCases* CClimbToHillBot::SelectCase(list<CCases*>& CurrentCases)
{
	multimap <float, CCases*> Sorter;

	for (auto it = CurrentCases.begin(); it != CurrentCases.end(); it++)
	{
		CCases* tempCase = *it;
		float CteGainProm = 0;
		list<CChoiceEvent*> lsttmpEvents=tempCase->m_lChoiceEvents;
		//tempCase->m_fH = (tempCase->Promise*tempCase->PickRandomEvent()->CteofGain) - tempCase->Cost;
		for (int i = 0; i < 5; i++)
		{
			CteGainProm += lsttmpEvents.back()->CteofGain;
			lsttmpEvents.pop_back();
		}
		CteGainProm = CteGainProm / 5;
		tempCase->m_fH = (tempCase->Promise*CteGainProm) - tempCase->Cost;
		Sorter.insert(make_pair(tempCase->m_fH, tempCase));
	}

	list <CCases*> lsttempCases;

	for (auto itS = Sorter.rbegin(); itS != Sorter.rend(); itS++)
		lsttempCases.push_front(itS->second);
	
	CCases* tempCase;

	tempCase = lsttempCases.back();
	tempCase->m_fH = (tempCase->Promise*tempCase->PickRandomEvent()->CteofGain) - tempCase->Cost;

	return tempCase;
	//return lsttempCases.back();
}
