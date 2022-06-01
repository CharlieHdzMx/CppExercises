#pragma once
#include <set>
#include "GraphManager.h"
#include <Windows.h>
#include <map>

using namespace std;

class CGraph
{
	friend class CGraphManager;

	CGraphManager* m_pGraphManager;

public:
	multimap<unsigned long, unsigned long long > m_mmAdjOutput;

	multimap<unsigned long, unsigned long long >m_mmAdjInput;

	set <unsigned long> m_V;

	set<unsigned long long>m_E;

	void GetAdjInput(unsigned long ulIDV, set<unsigned long long>& setAdjInput);

	void GetAdjOutput(unsigned long ulIDV, set<unsigned long long>& setAdjOutput);

	unsigned long OutputDegree(unsigned long ulIDV);

	unsigned long InputDegree(unsigned long ulIDV);

	void GetAdj(unsigned long ulID,set <unsigned long long>& setAdj);

	unsigned long GetKeyGraph()const;

	bool connect(unsigned long ulIDFirst, unsigned long ulIDSecond);

	bool disconnect(unsigned long ulIDFirst, unsigned long ulIDSecond);

	void DrawGraph(HDC hdc);

	unsigned long CGraph::Degree(unsigned long ulID);

	bool DeepFirstSearch(unsigned long ulIDSource, unsigned long ulIDDest);

	void Expansion(unsigned long ulID, set<unsigned long>& setExpansion);

	bool BreadthFirstSearch(unsigned long ulIDSource, unsigned long ulIDDest);

	CGraphManager* GetManager(){ return m_pGraphManager; };

	bool BackTracking(HDC hdc, unsigned long ulIDDest, unsigned long ulIDSource);

	float BackTrackingCost(unsigned long ulIDSource, unsigned long ulIDCurrent, float acumulate);

	void Contraction(unsigned long ulIDV, set<unsigned long>& setContraction);

protected:
	unsigned long m_ulID;

	CGraph();

	virtual ~CGraph();
};

