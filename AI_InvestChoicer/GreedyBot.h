#pragma once
#include "Bot.h"



class CGreedyBot :
	public CBot
{
public:
	CGreedyBot();
	virtual ~CGreedyBot();
	// En esta especializacion, el Greedybot solamente toma en cuenta la mejor promesa, es decir que ordena por promise
	CCases* SelectCase(list<CCases*>& CurrentCases);
};
