#include "stdafx.h"
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
#include <deque>


CGraph::CGraph()
{
}


CGraph::~CGraph()
{
}

bool CGraph::connect(unsigned long ulIDFirst, unsigned long ulIDSecond)
{
	if (m_pGraphManager->CreateEdge(ulIDFirst, ulIDSecond))
	{
		m_V.insert(ulIDFirst);
		m_V.insert(ulIDSecond);

		//x64:	x32ulIDSecond-x32ulIDFirst
		unsigned long long ullID = ulIDSecond;
		ullID <<= 32;
		ullID |= ulIDFirst;

		m_E.insert(ullID);
		m_mmAdjInput.insert(make_pair(ulIDSecond,ullID));
		m_mmAdjOutput.insert(make_pair(ulIDFirst,ullID));
		
		return true;
	}

	return false;
}

bool CGraph::disconnect(unsigned long ulIDFirst, unsigned long ulIDSecond){


	if (m_pGraphManager->CreateEdge(ulIDFirst, ulIDSecond))
	{
		unsigned long long ullID = ulIDSecond;
		ullID <<= 32;
		ullID |= ulIDFirst;

		multimap<unsigned long, unsigned long long>m_respaldo;

		for (auto it = m_mmAdjInput.begin(); it != m_mmAdjInput.end(); it++)
			m_respaldo.insert(*it);

		m_mmAdjInput.clear();
		
		for (auto it1 = m_respaldo.begin(); it1 != m_respaldo.end(); it1++)
		{
			if (it1->second != ullID)
				m_mmAdjInput.insert(*it1);
		}

		m_respaldo.clear();


		for (auto it = m_mmAdjOutput.begin(); it != m_mmAdjOutput.end(); it++)
			m_respaldo.insert(*it);

		m_mmAdjOutput.clear();

		for (auto it1 = m_respaldo.begin(); it1 != m_respaldo.end(); it1++)
		{
			if (it1->second != ullID)
				m_mmAdjOutput.insert(*it1);
		}

		m_E.erase(ullID);
		return TRUE;
	}

	return FALSE;
}

void CGraph::DrawGraph(HDC hdc){
	
	for (auto itE = m_E.begin(); itE != m_E.end(); itE++)
	{
		union{
			struct{
				unsigned long l_ulIDFirst;
				unsigned long l_ulIDSecond;
			};
			unsigned long long l_ullID;
		};

		l_ullID = *itE;
		m_pGraphManager->CreateEdge(l_ulIDFirst, l_ulIDSecond)->DrawEdge(hdc);
	}

	for (auto itV = m_V.begin(); itV != m_V.end(); itV++)
		m_pGraphManager->CreateVertex(*itV)->DrawVertex(hdc);
}

unsigned long CGraph::GetKeyGraph()const
{
	return m_ulID;
}

void CGraph::GetAdjOutput(unsigned long ulIDV, set<unsigned long long>& setAdjOutput){

	auto Range = m_mmAdjOutput.equal_range(ulIDV);
	
	for (auto it = Range.first; it != Range.second; it++)
		setAdjOutput.insert(it->second);
}

unsigned long CGraph::OutputDegree(unsigned long ulIDV){

	set<unsigned long long> setAdjOutput;
	GetAdjOutput(ulIDV, setAdjOutput);
	return setAdjOutput.size();
}

void CGraph::GetAdjInput(unsigned long ulIDV, set<unsigned long long>& setAdjInput){

	auto Range = m_mmAdjInput.equal_range(ulIDV);

	for (auto it = Range.first; it != Range.second; it++)
		setAdjInput.insert(it->second);
}

unsigned long  CGraph::InputDegree(unsigned long ulIDV){

	set<unsigned long long> setAdjInput;
	GetAdjInput(ulIDV, setAdjInput);
	return setAdjInput.size();
}

unsigned long CGraph::Degree(unsigned long ulID)
{
	set<unsigned long long> setAdj;
	GetAdj(ulID, setAdj);
	return setAdj.size();

}

void CGraph::GetAdj(unsigned long ulID,set<unsigned long long>& SetAdj){
	

	auto RangeI = m_mmAdjInput.equal_range(ulID);
	for (auto it = RangeI.first; it != RangeI.second; it++)
		SetAdj.insert(it->second);

	auto RangeO = m_mmAdjOutput.equal_range(ulID);
	for (auto it = RangeO.first; it != RangeO.second; it++)
		SetAdj.insert(it->second);

}

bool CGraph::DeepFirstSearch(unsigned long ulIDSource, unsigned long ulIDDest)
{
	set<unsigned long> Exp;
	Expansion(ulIDSource, Exp);

	for (auto it = Exp.begin(); it != Exp.end(); it++)
	{
		CVertex* pV = m_pGraphManager->CreateVertex(*it);
		if (!pV->m_bVisited)
		{
			pV->m_bVisited = true;
			pV->m_ulIDParent = ulIDSource;

			if (*it == ulIDDest)
				return true;

			if (DeepFirstSearch(*it, ulIDDest))
			{
				return true;
			}
		}
	}

	return false;
}

void CGraph::Expansion(unsigned long ulID, set<unsigned long>& setExpansion)
{
	set<unsigned long long> setAdjOutput;
	GetAdjOutput(ulID, setAdjOutput);

	for (auto it = setAdjOutput.begin(); it != setAdjOutput.end(); it++)
	{
		unsigned long long l_ullID=*it;
		l_ullID >>= 32;
		unsigned long ulIDSecond = (unsigned long) l_ullID;
		setExpansion.insert(ulIDSecond);
	}
}

void CGraph::Contraction(unsigned long ulIDV, set<unsigned long>& setContraction)
{
	set<unsigned long long> l_setInput;
	GetAdjInput(ulIDV, l_setInput);

	for (auto it = l_setInput.begin(); it != l_setInput.end(); it++)
	{
		unsigned long ulIDFirst = *it;
		setContraction.insert(ulIDFirst);
	}
}

bool CGraph::BreadthFirstSearch(unsigned long ulIDSource, unsigned long ulIDDest)
{
	deque<unsigned long> Q;
	Q.push_back(ulIDSource);

	while (!Q.empty())
	{
		unsigned long ulV = Q.front();
		Q.pop_front();
		set <unsigned long> Exp;
		Expansion(ulV, Exp);

		for (auto it = Exp.begin(); it != Exp.end(); it++)
		{
			CVertex* pW = m_pGraphManager->CreateVertex(*it);

			if (!pW->m_bVisited)
			{

				pW->m_bVisited = true;
				pW->m_ulIDParent = ulV;
				Q.push_back(*it);

				if (*it == ulIDDest)
					return true;
			}
		}
	}


	return false;
}

bool CGraph::BackTracking(HDC hdc, unsigned long ulIDDest, unsigned long ulIDSource)
{
	CVertex* pV = m_pGraphManager->CreateVertex(ulIDDest);
	CVertex* pVParent = m_pGraphManager->CreateVertex(pV->m_ulIDParent);
	
	MoveToEx(hdc, pV->m_fx, pV->m_fy,NULL);
	LineTo(hdc, pVParent->m_fx, pVParent->m_fy);

	if (pVParent->GetKey() == ulIDSource)
		return true;

	return BackTracking(hdc, pVParent->GetKey(), ulIDSource);
}

float CGraph::BackTrackingCost(unsigned long ulIDSource, unsigned long ulIDCurrent,float acumulate)
{

	float dx, dy;

	if (ulIDSource == ulIDCurrent)
		return acumulate;

	CVertex* VParent, *VCurrent;

	VCurrent = m_pGraphManager->CreateVertex(ulIDCurrent);
	VParent = m_pGraphManager->CreateVertex(ulIDSource);

	dx = VCurrent->m_fx - VParent->m_fx;
	dy = VCurrent->m_fy - VParent->m_fy;

	acumulate += sqrt(dx*dx + dy*dy);

	return BackTrackingCost(ulIDSource, VCurrent->m_ulIDParent, acumulate);
}
