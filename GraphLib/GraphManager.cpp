#include "stdafx.h"
#include "GraphManager.h"
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"

CGraphManager::CGraphManager()
{
}


CGraphManager::~CGraphManager()
{
}

CGraph* CGraphManager::CreateGraph(unsigned long ulID)
{
	auto it = m_mGraphs.find(ulID);
	
	//Cuando el grafo ya existe
	if (it != m_mGraphs.end())
		return it->second;


	//Cuando el grafo todavia no existe
	else
	{
		CGraph* pGraph = new CGraph();
		pGraph->m_pGraphManager = this;
		pGraph->m_ulID = ulID;
		m_mGraphs.insert(make_pair(ulID,pGraph));
		return pGraph;
	}

}

CEdge* CGraphManager::CreateEdge(unsigned long ulIDFirst, unsigned long ulIDSecond)
{
	union
	{
		struct
		{
			unsigned long l_ulIDFirst;
			unsigned long l_ulIDSecond;
		};
		unsigned long long l_ullID;
	};
	l_ulIDFirst = ulIDFirst;
	l_ulIDSecond = ulIDSecond;

	auto it = m_mEdges.find(l_ullID);
	if (it != m_mEdges.end())
		return it->second;

	else
	{
		auto it = m_mVertex.find(ulIDFirst);
		if (it == m_mVertex.end())
			return 0;
		
		it = m_mVertex.find(ulIDSecond);
		if (it == m_mVertex.end())
			return 0;

		CEdge* pEdge = new CEdge();
		pEdge->m_ullID = l_ullID;
		pEdge->m_pGraphManager = this;
		pEdge->m_ulIDFirst = ulIDFirst;
		pEdge->m_ulIDSecond = ulIDSecond;
		m_mEdges.insert(make_pair(l_ullID, pEdge));
		return pEdge;

	}

}

CVertex* CGraphManager::CreateVertex(unsigned long ulID)
{
	auto it = m_mVertex.find(ulID);

	if (it != m_mVertex.end())
		return it->second;

	else
	{
		CVertex* pVertex = new CVertex();
		pVertex->m_ulID = ulID;
		pVertex->m_Manager = this;
		m_mVertex.insert(make_pair(ulID, pVertex));
		return pVertex;
	}

}