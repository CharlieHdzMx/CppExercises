#include "stdafx.h"
#include "SearchStrategyBestFirst.h"


CSearchStrategyBestFirst::CSearchStrategyBestFirst()
{
}


CSearchStrategyBestFirst::~CSearchStrategyBestFirst()
{
}

unsigned long CSearchStrategyBestFirst::PeekFromOpenList(){

	unsigned long ulV = m_lstOpen.front();
	m_lstOpen.pop_front();
	return ulV;
}

void CSearchStrategyBestFirst::InsertToClosedList(unsigned long ulIDV){
	m_setClosed.insert(ulIDV);

}

void CSearchStrategyBestFirst::Expand(unsigned long ulIDV, set<unsigned long>& setExp){

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

void CSearchStrategyBestFirst::EvalHeuristicFunction(unsigned long ulIDV, unsigned long ulIDW, unsigned long ulIDM){

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

void CSearchStrategyBestFirst::Merge(set<unsigned long>& setExp){

	multimap <float, unsigned long> Sorted;
	CVertex* pV;

	//Inserta setExp a Sorted
	for (auto it = setExp.begin(); it != setExp.end(); it++)
	{
		pV = m_pGraph->GetManager()->CreateVertex(*it);
		Sorted.insert(make_pair(pV->m_fh, *it));
	}

	//Itera la lista de abiertos
	for (auto it2 = m_lstOpen.begin(); it2 != m_lstOpen.end(); it2++)
	{
		pV = m_pGraph->GetManager()->CreateVertex(*it2);
		Sorted.insert(make_pair(pV->m_fh, *it2));
	}

	m_lstOpen.clear();

	//Traspasar ya ordenados las claves de aristas 
	for (auto it3 = Sorted.begin(); it3 != Sorted.end(); it3++)
		m_lstOpen.push_back(it3->second);

}