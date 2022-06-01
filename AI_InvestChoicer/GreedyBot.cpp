#include "stdafx.h"
#include "GreedyBot.h"
#include <map>

using namespace std;

CGreedyBot::CGreedyBot()
{
}


CGreedyBot::~CGreedyBot()
{
}


// En esta especializacion, el Greedybot solamente toma en cuenta la mejor promesa, es decir que ordena por promise
CCases* CGreedyBot::SelectCase(list<CCases*>& CurrentCases)
{
	multimap<unsigned int, CCases*> Sorter;

	for (auto it = CurrentCases.begin(); it != CurrentCases.end(); it++)
	{
		CCases* tempCase = *it;
		//tempCase->m_fH = tempCase->Promise;

		Sorter.insert(make_pair(tempCase->Promise, tempCase));
	}

	list<CCases*> listtempCases;

	for (auto it1 = Sorter.rbegin(); it1 != Sorter.rend(); it1++)
		listtempCases.push_front(it1->second);

	CCases* tempCase;

	tempCase = listtempCases.back();
	tempCase->m_fH = (tempCase->Promise*tempCase->PickRandomEvent()->CteofGain) - tempCase->Cost;

	return tempCase;

	//return listtempCases.back();
}
