#pragma once
#include "InvestChoiceEnviroment.h"
#include <list>

class InvestChoiceEnviroment;
using namespace std;

//Esta clase no se puede implementar directamente
class CBot
{
public:
	bool continua = 1;
	int m_nMoneyAmount;
	CBot();
	virtual ~CBot();


	// Decision de los 3 diferentes casos que se les presenta, involucrando todo las consecuencias de esta accion
	bool Decide(list<CCases*>& CurrentCases);
	// Implentacion de Seleccion de caso, depende de que tipo de bot va a utilizarlo
	virtual CCases* SelectCase(list<CCases*>& CurrentCases) = 0;
};

