#include "stdafx.h"
#include "SearchStrategyDFS.h"


CSearchStrategyDFS::CSearchStrategyDFS()
{
}


CSearchStrategyDFS::~CSearchStrategyDFS()
{
}

unsigned long CSearchStrategyDFS::PeekFromOpenList(){
	unsigned long ulV = m_lstOpen.back();
	m_lstOpen.pop_back();
	return ulV;
}

void CSearchStrategyDFS::InsertToClosedList(unsigned long ulIDV){

	m_setClosed.insert(ulIDV);
}

void CSearchStrategyDFS::Expand(unsigned long ulIDV, set<unsigned long>& setExp){

	set <unsigned long> l_setExp;
	m_pGraph->Expansion(ulIDV, l_setExp);
	set_difference(l_setExp.begin(), l_setExp.end(), m_setClosed.begin(), m_setClosed.end(), inserter(setExp, setExp.end()));

	CVertex* pV;

	for (auto it = setExp.begin(); it != setExp.end(); it++){

		pV = m_pGraph->GetManager()->CreateVertex(*it);
		pV->m_ulIDParent = ulIDV;
	}
}

void CSearchStrategyDFS::Merge(set <unsigned long>& setExp){
	 
	for (auto it = setExp.begin(); it != setExp.end(); it++)
		m_lstOpen.push_back(*it);

}

void CSearchStrategyDFS::EvalHeuristicFunction(unsigned long ulIDV, unsigned long ulIDW, unsigned long ulIDM){

	//NULO
}