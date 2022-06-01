#pragma once
#include "Bot.h"
#include <list>

using namespace std;


class CDepthBot :
	public CBot
{
public:

	CDepthBot();
	virtual ~CDepthBot();


	// //Especializacion de como insertar el caso a elegir
	CCases* SelectCase(list<CCases*>& CurrentCases);
};

