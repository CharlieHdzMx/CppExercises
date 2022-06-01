#include "stdafx.h"
#include "SearchStrategyGreedy.h"


CSearchStrategyGreedy::CSearchStrategyGreedy()
{
}


CSearchStrategyGreedy::~CSearchStrategyGreedy()
{
}


unsigned long CSearchStrategyGreedy::PeekFromOpenList(){

	unsigned long ulV = *m_lstOpen.begin();
	m_lstOpen.erase(m_lstOpen.begin());
	return ulV;
}

void CSearchStrategyGreedy::InsertToClosedList(unsigned long ulIDV){
	
	m_setClosed.insert(ulIDV);
}

void CSearchStrategyGreedy::Expand(unsigned long ulIDV, set<unsigned long>& setExp){

	set<unsigned long> l_setExp;
	m_pGraph->Expansion(ulIDV, l_setExp);

	set_difference(l_setExp.begin(), l_setExp.end(), m_setClosed.begin(), m_setClosed.end(), inserter(setExp, setExp.end()));

	CVertex* pV;
	for (auto it = setExp.begin(); it != setExp.end(); it++)
	{
		pV = m_pGraph->GetManager()->CreateVertex(*it);
		pV->m_ulIDParent = ulIDV;
	}


}

void CSearchStrategyGreedy::EvalHeuristicFunction(unsigned long ulIDV, unsigned long ulIDW, unsigned long ulIDM){

	CVertex* pCurrent, *pObjective;

	pCurrent = m_pGraph->GetManager()->CreateVertex(ulIDW);
	pObjective = m_pGraph->GetManager()->CreateVertex(ulIDM);

	float dx, dy;

	dx = pObjective->m_fx - pCurrent->m_fx;
	dy = pObjective->m_fy - pCurrent->m_fy;

	pCurrent->m_fh = sqrt(dx*dx + dy*dy);

}

void  CSearchStrategyGreedy::Merge(set<unsigned long>& setExp){

	multimap<float, unsigned long> Sorted;
	CVertex *pV;
		
	for (auto it = setExp.begin(); it != setExp.end(); it++)
	{
		pV = m_pGraph->GetManager()->CreateVertex(*it);
		Sorted.insert(make_pair(pV->m_fh, *it));
	}

	for (auto it2 = Sorted.rbegin(); it2 != Sorted.rend(); it2++)
		m_lstOpen.push_front(it2->second);

}
