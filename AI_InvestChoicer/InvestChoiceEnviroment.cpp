#include "stdafx.h"
#include "InvestChoiceEnviroment.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

InvestChoiceEnviroment::InvestChoiceEnviroment()
{

}


InvestChoiceEnviroment::~InvestChoiceEnviroment()
{
}


/*
Nombre de caso
Precio
Promesa
Descripcion evento 1
Cte Evento1
Descripcion evento 2
CteEvento2
Descripcion evento 3
CteEvento3
Descripcion evento 4
CteEvento4
DescripcionEvento 5
CteEvento 5

EOF

*/

// Carga los casos requeridos desde un archivo exterior de texto

//Estructura: Primero verifica si el archivo fue correctamente abierto, normalmente no lo abre si no esta en la direccion del proyecto
//Para cada caso que se va a cargar  se crea un objecto temporal de CCases y inserta el nombre, costo y promesa del archivo a las variables correspondientes, e inserta la descripcion y cte de gganancia de todos los eventos que tiene ese caso , cuando termina de copiar inserta esos eventos a la lista de eventos de la clase correspondiente y cuando este insertado todo de ese caso se guarda en la lista de casos y se procede hasta que no haya casos y se cierra el archivo.
void InvestChoiceEnviroment::LoadCases()
{
	int n=0;

	ifstream myFile("Cases.txt", ios::in);

	if (!myFile)
	{
		cout << "The file could not be opened" << endl;
		exit(1);
	}

	for (unsigned int i = 0; i < 35; i++)
	{
		CCases* pCases = new CCases;
		myFile.seekg(n);
		getline(myFile,pCases->Name);
		myFile >> pCases->Cost;
		myFile >> pCases->Promise;
		myFile.ignore();
		n = myFile.tellg();
		for (unsigned int j = 0; j < 5; j++)
		{
			CChoiceEvent* pEvent = new CChoiceEvent;
			myFile.seekg(n);
			getline(myFile,pEvent->Description);
			myFile >> pEvent->CteofGain;
			myFile.ignore();
			n = myFile.tellg();
			pCases->m_lChoiceEvents.push_front(pEvent);
		}
		m_lCases.push_front(pCases);
	}
	myFile.close();
}


// Metodo que inserta a una lista los casos en la que su costo pueda invertirlo el jugador, asi evitando agregar Casos que el jugador no pueda pagar, esta lista sera el que eventualmente se estara usando. Retorna la lista si se insertaron 3 casos exitosamente y de otra forma retorna 0

//int random_integer;
//random_integer=/(rand()%30)+1;
list<CCases*> InvestChoiceEnviroment::ExtractCurrentCases(float m_fAmount)
{
	LoadCases();

	unsigned int k = 0;
	list<CCases*> CurrentCasesList;
	CCases* CurrentCase;
	unsigned int count;
	int random_integer;

	vector<CCases*> tmp;
	for (auto it = m_lCases.begin(); it != m_lCases.end(); it++)
	{
		CurrentCase = *it;
		if (CurrentCase->Cost <= m_fAmount)
			tmp.push_back(CurrentCase);
	}
	for (int k = 0; k < 3; k++)
	{
		random_integer = rand() % tmp.size();
		CurrentCasesList.push_front(tmp[random_integer]);
	}
	return CurrentCasesList;


	
	//Falta determinar como NoValido cuando la lista no tiene los 3 casos pero esto se puede implementar fuera de este metodo
}



// Plantilla de creacion de un InvestEnviroment
void InvestChoiceEnviroment::CreateInvestEnviroment()
{

	unsigned int i = 1;
	//Conexion del vertice del jugador con los Cases.
	m_pInvestGraph=m_GraphManager.CreateGraph(0);
	m_pCurrentPlayer->m_pPlayerVertex = m_GraphManager.CreateVertex(i);

	//Coordenadas fijas del vertice
	m_pCurrentPlayer->m_pPlayerVertex->m_fx = 600;
	m_pCurrentPlayer->m_pPlayerVertex->m_fy = 300;
	for (unsigned int j = 0; j < 3; j++)
	{
		CVertex* pTempVertex;
		i++;

		pTempVertex = m_GraphManager.CreateVertex(i);
		pTempVertex->m_fx = 100 * (i-1);
		pTempVertex->m_fy = 50;
		m_pInvestGraph->connect(m_pCurrentPlayer->m_pPlayerVertex->GetKey(), pTempVertex->GetKey());
	}
	
}


// En cada ciclo de casos de seleccion verifica la cantidad minima de inversion y a partir de ahi elige que casos conectar
list<CCases*> InvestChoiceEnviroment::RefreshCases(float MinimumCost)
{

	list<CCases*> templstCases;

	templstCases=ExtractCurrentCases(MinimumCost);

	if (templstCases.size() == 3)
	{
		unsigned int i = 1;
		m_pInvestGraph->m_mmAdjOutput.clear();
		m_pInvestGraph->m_mmAdjInput.clear();

		for (auto it = templstCases.begin(); it != templstCases.end(); it++)
		{
			CCases* CurrentCase = *it;
			i++;
			CurrentCase->m_pCaseVertex = m_GraphManager.CreateVertex(i);
			CurrentCase->m_pCaseVertex->m_fy = 100;
			CurrentCase->m_pCaseVertex->m_fx =200 + (400 * (i -2));
			m_pInvestGraph->connect(m_pCurrentPlayer->m_pPlayerVertex->GetKey(), CurrentCase->m_pCaseVertex->GetKey());
		}
	}

	else
		exit(1);

	return templstCases;

}
