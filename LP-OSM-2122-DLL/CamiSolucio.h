#pragma once
#include "pch.h"
#include "CamiBase.h"

using namespace std;

class CamiSolucio : public CamiBase
{
public:
	CamiSolucio() {}
	~CamiSolucio() {}

	std::vector<Coordinate> getCamiCoords();

private:
	vector<Coordinate> m_Coordinates;
};
