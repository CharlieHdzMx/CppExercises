#pragma once
#include "..\GraphLib\Graph.h"
#include "..\GraphLib\Vertex.h"

class CPlayer
{
public:
	CVertex m_PlayerVertex;

	CVertex* m_pPlayerVertex;

	float m_fMoneyAmount;

	CPlayer();
	virtual ~CPlayer();
};

