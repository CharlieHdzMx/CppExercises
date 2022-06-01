#pragma once
#include "SearchStrategy.h"

class CSearchStrategyGreedy :
	public CSearchStrategy
{
public:
	CSearchStrategyGreedy();
	virtual ~CSearchStrategyGreedy();

protected:
	virtual unsigned long PeekFromOpenList();
	virtual void InsertToClosedList(unsigned long ulIDV);
	virtual void Expand(unsigned long ulIDV, set<unsigned long>& setExp);
	virtual void EvalHeuristicFunction(unsigned long ulIDV, unsigned long ulIDW, unsigned long ulIDM);
	virtual void Merge(set<unsigned long>& setExp);
};

