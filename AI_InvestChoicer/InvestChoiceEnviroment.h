#pragma once
#include "..\GraphLib\Graph.h"
#include <list>
#include "Cases.h"
#include "ChoiceEvent.h"
#include "Player.h"
#include "Bot.h"
#include "..\GraphLib\GraphManager.h"

using namespace std;

class InvestChoiceEnviroment
{
public:
	CGraphManager m_GraphManager;

	CGraph* m_pInvestGraph;

	CPlayer* m_pCurrentPlayer;

	list<CCases*> m_lCases;
	InvestChoiceEnviroment();
	virtual ~InvestChoiceEnviroment();

	// Carga los casos requeridos desde un archivo exterior de texto
	void LoadCases();

	// Metodo que inserta a una lista los casos en la que su costo pueda invertirlo el jugador, asi evitando agregar Casos que el jugador no pueda pagar, esta lista sera el que eventualmente se estara usando. Retorna la lista si se insertaron 3 casos exitosamente y de otra forma retorna 0
	list<CCases*> ExtractCurrentCases(float m_fAmount);
	// Plantilla de creacion de un InvestEnviroment
	void CreateInvestEnviroment();
	// En cada ciclo de casos de seleccion verifica la cantidad minima de inversion y a partir de ahi elige que casos conectar
	list<CCases*> RefreshCases(float MinimumCost);
};

