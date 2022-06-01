#include "stdafx.h"
#include "SearchStrategyClimbTheHill.h"


CSearchStrategyClimbTheHill::CSearchStrategyClimbTheHill()
{
}


CSearchStrategyClimbTheHill::~CSearchStrategyClimbTheHill()
{
}


unsigned long CSearchStrategyClimbTheHill::PeekFromOpenList(){

	unsigned long ulIDV = m_lstOpen.front();
	m_lstOpen.pop_front();
	return ulIDV;

}
void CSearchStrategyClimbTheHill::InsertToClosedList(unsigned long ulIDV){

	m_setClosed.insert(ulIDV);
}

void CSearchStrategyClimbTheHill::Expand(unsigned long ulIDV, set<unsigned long>& setExp){

	set<unsigned long> l_setExp;
	m_pGraph->Expansion(ulIDV, l_setExp);
	set_difference(l_setExp.begin(), l_setExp.end(), m_setClosed.begin(), m_setClosed.end(),
		inserter(setExp, setExp.end()));

	CVertex *pV;

	for (auto it = setExp.begin(); it != setExp.end(); ++it)
	{
		pV = m_pGraph->GetManager()->CreateVertex(*it);
		pV->m_ulIDParent = ulIDV;
	}
}

void CSearchStrategyClimbTheHill::EvalHeuristicFunction(unsigned long ulIDV, unsigned long ulIDW, unsigned long ulIDM){

	CVertex *pCurrent;
	CVertex	*pDest;

	pCurrent = m_pGraph->GetManager()->CreateVertex(ulIDW);
	pDest = m_pGraph->GetManager()->CreateVertex(ulIDM);

	float dHx, dHy;
	static float l_h;
	static float l_g;

	dHx = pDest->m_fx - pCurrent->m_fx;
	dHy = pDest->m_fy - pCurrent->m_fy;

	l_h = sqrt(dHx*dHx + dHy*dHy);

	l_g = m_pGraph->BackTrackingCost(ulIDV, ulIDW, 0);

	pCurrent->m_fh = l_g + l_h;
}

void CSearchStrategyClimbTheHill::Merge(set<unsigned long>& setExp){

	multimap<float, unsigned long> Sorted;
	CVertex* pV;

	for (auto it = setExp.begin(); it != setExp.end(); it++)
	{
		pV = m_pGraph->GetManager()->CreateVertex(*it);
		Sorted.insert(make_pair(pV->m_fh, *it));
	}

	for (auto it2 = Sorted.rbegin(); it2 != Sorted.rend(); it2++)
		m_lstOpen.push_front(it2->second);

}