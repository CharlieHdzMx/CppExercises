#include "stdafx.h"
#include "Bot.h"
#include <iterator>
#include <algorithm>

using namespace std;


CBot::CBot()
{
}


CBot::~CBot()
{
}



// Decision de los 3 diferentes casos que se les presenta, involucrando todo las consecuencias de esta accion
bool CBot::Decide( list<CCases*>& lCurrentCases)
{
	int cont = 0;
	list<CCases*> tmplst = lCurrentCases;
	for (auto it = lCurrentCases.begin(); it != lCurrentCases.end(); it++)
	{
		CCases* Caso = *it;
		if (m_nMoneyAmount < Caso->Cost)
		{
			tmplst.pop_front();
			cont++;
		}
		if (cont == 3)
			return 0;
	}
	CCases* SelectedCase=SelectCase(tmplst);
			
	m_nMoneyAmount += SelectedCase->m_fH;
	return 1;
}
