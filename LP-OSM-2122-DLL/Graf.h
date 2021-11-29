#pragma once
#include <string>
#include <vector>
#include <list>
#include "Common.h"

using namespace std;

class Graf
{
public:
	Graf(vector<Coordinate> coordinate_List);
	~Graf();
	void AfegirNode(string node_Name);
	void AfegirAresta(int position_Node1, int position_Node2);
	void AfegirAresta(int weight);
	void deleteRepetedCoordinates(vector<Coordinate>& coordinate_list);

private:
	vector<list<pair<int, double>>> m_Neighbors;
	vector<string> m_nodes;
	int m_NumNodes;
	int m_NumLinks;
};

Graf::Graf(vector<Coordinate> coordinate_List)
{
	deleteRepetedCoordinates(coordinate_List);
	m_NumNodes = coordinate_List.size();

}

Graf::~Graf()
{
}

void deleteRepetedCoordinates(vector<Coordinate>& coordinate_list)
{
	auto coordinate_List_end = coordinate_list.end();
	for (auto it_Coordinate_List = coordinate_list.begin(); it_Coordinate_List != coordinate_List_end; ++it_Coordinate_List)
	{
		coordinate_List_end = remove(it_Coordinate_List++, coordinate_List_end, *it_Coordinate_List);
	}

	coordinate_list.erase(coordinate_List_end, coordinate_list.end());
}