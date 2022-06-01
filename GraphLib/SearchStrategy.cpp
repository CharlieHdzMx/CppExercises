#include "stdafx.h"
#include "SearchStrategy.h"

unsigned long CSearchStrategy::s_ulIDSource = 0;

CSearchStrategy::CSearchStrategy()
{
	
}


CSearchStrategy::~CSearchStrategy()
{
}

bool CSearchStrategy::Search(CGraph* pGraph, unsigned long ulIDSource, unsigned long ulIDDest){

	m_lstOpen.clear();
	m_setClosed.clear();
	s_ulIDSource = ulIDDest;

	m_pGraph = pGraph;
	m_lstOpen.push_back(ulIDSource); 

	while (!m_lstOpen.empty()){
		unsigned long ulV = PeekFromOpenList();
		InsertToClosedList(ulV);
		if (ulV == ulIDDest)
		{
			bValidateSource = true;
			return true;
		}

		set<unsigned long> setExp;
		Expand(ulV, setExp);

		for (auto itW = setExp.begin(); itW != setExp.end(); itW++)
			EvalHeuristicFunction(ulV, *itW, ulIDDest);

		Merge(setExp);
	}
	return false;
}