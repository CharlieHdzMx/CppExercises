#include "stdafx.h"
#include "DepthBot.h"


CDepthBot::CDepthBot()
{
}


CDepthBot::~CDepthBot()
{
}



// //Especializacion de como insertar el caso a elegir
CCases* CDepthBot::SelectCase(list<CCases*>& CurrentCases)
{
	CCases* tempCase;

	tempCase = CurrentCases.front();
	tempCase->m_fH = (tempCase->Promise*tempCase->PickRandomEvent()->CteofGain) - tempCase->Cost;

	return tempCase;
}
