#pragma once
#include <string>
#include <vector>
#include <list>
#include "Common.h"
#include "Util.h"

using namespace std;

class Graf
{
public:
	Graf() : m_Num_Links(0), m_Num_Nodes(0) {}
	Graf(vector<CamiSolucio*> coordinate_List);
	~Graf() {}
	void AfegirNode();
	void AfegirAresta(int position_Node1, int position_Node2);
	void AfegirAresta(int weight);
	int findIndex(Coordinate coordinate);

private:
	vector<list<pair<int, double>>> m_Neighbors;
	vector<Coordinate> m_nodes; //Does not accept repeted values
	int m_Num_Nodes;
	int m_Num_Links;
};

Graf::Graf(vector<CamiSolucio*> coordinate_matrix)
{
	for (int it_Row = 0; it_Row < coordinate_matrix.size(); it_Row++)
	{
		vector<Coordinate> coordinate_Vector = (*coordinate_matrix[it_Row]).getCamiCoords();
		for (int it_Column = 0; it_Column < coordinate_Vector.size(); it_Column++)
		{
			vector<Coordinate>::iterator it = std::find(m_nodes.begin(), m_nodes.end(), coordinate_Vector[it_Column]);
			if (it == m_nodes.end())
			{
				m_nodes.emplace_back(coordinate_Vector[it_Column]);
			}
		}
	}

	m_Num_Nodes = m_nodes.size();
	m_Neighbors.resize(m_Num_Nodes);
	m_Num_Links = 0;

	for (int it_Row = 0; it_Row < coordinate_matrix.size(); it_Row++)
	{
		vector<Coordinate> coordinate_Vector = (*coordinate_matrix[it_Row]).getCamiCoords();
		for (int it_Column = 0; it_Column < coordinate_Vector.size() - 1; it_Column++)
		{
			int coordinate_First_Index = findIndex(coordinate_Vector[it_Column]);
			int coordinate_Second_Index = findIndex(coordinate_Vector[it_Column + 1]);
			if (coordinate_First_Index != -1 && coordinate_Second_Index != -1)
			{
				double weight = Util::DistanciaHaversine(coordinate_Vector[it_Column], coordinate_Vector[it_Column + 1]);
				m_Neighbors[coordinate_First_Index].emplace_back(pair<int, double>(coordinate_Second_Index, weight));
				m_Neighbors[coordinate_Second_Index].emplace_back(pair<int, double>(coordinate_First_Index, weight));
				m_Num_Links++;
			}
		}
	}
}


int Graf::findIndex(Coordinate coordinate)
{
	for (int i = 0; i < m_Num_Nodes; i++)
	{
		if(m_nodes[i].lat == coordinate.lat && m_nodes[i].lon == coordinate.lon)
			return i;
	}

	return -1;
}
