#pragma once
#include <map>

using namespace std;

class CVertex;
class CEdge;
class CGraph;

class CGraphManager
{
protected:

	map<unsigned long,CVertex*> m_mVertex;
	map<unsigned long long, CEdge*> m_mEdges;
	map<unsigned long , CGraph*> m_mGraphs;
	

public:

	CVertex* CreateVertex(unsigned long ulID);

	CEdge* CreateEdge(unsigned long ulIDFirst, unsigned long ulIDSecond);

	CGraph* CreateGraph(unsigned long ulID);

	CGraphManager();

	virtual ~CGraphManager();
};

