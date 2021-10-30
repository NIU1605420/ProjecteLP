#pragma once
#include "Common.h"
#include "CamiBase.h"

using namespace std;

class CamiSolucio : public CamiBase 
{
public:
	CamiSolucio() {}
	~CamiSolucio() {}

	vector<Coordinate> getCamiCoords() { return m_Coordinates; }

private:
	vector<Coordinate> m_Coordinates;
};
