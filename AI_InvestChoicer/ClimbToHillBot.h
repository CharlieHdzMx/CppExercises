#pragma once
#include "Bot.h"


class CClimbToHillBot :
	public CBot
{
public:
	CClimbToHillBot();
	virtual ~CClimbToHillBot();
	// Especializacion del interfaz de SelectCase que toma en cuenta la heuristica y el costo.Este implementa un contenedor multimap para poder ordenar los casos por su heuristica-costo y despues  de esto tomar el de mayor diferencia promesa.costo
	virtual CCases* SelectCase(list<CCases*>& CurrentCases);
};

