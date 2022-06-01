#pragma once
#include <set>
#include <list>
#include <algorithm>
#include <iterator>
#include "Graph.h"
#include "Edge.h"
#include "GraphManager.h"
#include "Vertex.h"

using namespace std;

class CSearchStrategy
{
public:

	set<unsigned long>m_setClosed;

	list<unsigned long> m_lstOpen;

	CGraph* m_pGraph;

	bool Search(CGraph* pGraph,unsigned long ulIDSource,unsigned long ulIDDest);

	CSearchStrategy();

	virtual ~CSearchStrategy();

protected:
	static unsigned long s_ulIDSource;
	static bool bValidateSource;
	virtual unsigned long PeekFromOpenList() = 0;
	virtual void InsertToClosedList(unsigned long ulIDV) = 0;
	virtual void Expand(unsigned long ulIDV, set<unsigned long>& setExp) = 0;
	virtual void EvalHeuristicFunction(unsigned long ulIDV, unsigned long ulIDW, unsigned long ulIDM) = 0;
	virtual void Merge(set<unsigned long>& setExp) = 0;
};

