#include "stdafx.h"
#include "SearchStrategyBFS.h"

bool CSearchStrategy::bValidateSource = true;

CSearchStrategyBFS::CSearchStrategyBFS()
{
	
}


CSearchStrategyBFS::~CSearchStrategyBFS()
{
}

unsigned long CSearchStrategyBFS::PeekFromOpenList(){

	unsigned long ulIDV = m_lstOpen.front();
	m_lstOpen.pop_front();
	return ulIDV;

}
void CSearchStrategyBFS::InsertToClosedList(unsigned long ulIDV){

	m_setClosed.insert(ulIDV);
}


void CSearchStrategyBFS::Expand(unsigned long ulIDV, set<unsigned long>& setExp){
	set<unsigned long> l_setExp;
	m_pGraph->Expansion(ulIDV, l_setExp);

	set_difference(l_setExp.begin(), l_setExp.end(), m_setClosed.begin(), m_setClosed.end(), inserter(setExp, setExp.end()));

	CVertex* pV;

	for (auto it = setExp.begin(); it != setExp.end(); it++)
	{
		pV = m_pGraph->GetManager()->CreateVertex(*it);

		if (pV->GetKey() != s_ulIDSource)
			pV->m_ulIDParent = ulIDV;
		
		else
			if (bValidateSource)
			{
				pV->m_ulIDParent = ulIDV;
				bValidateSource = false;
			}

	}

}

void CSearchStrategyBFS::EvalHeuristicFunction(unsigned long ulIDV, unsigned long ulIDW, unsigned long ulIDM){
	


}


void CSearchStrategyBFS::Merge(set<unsigned long>& setExp)
{
	for (auto it = setExp.begin(); it != setExp.end(); it++)
		m_lstOpen.push_back(*it);
}