#pragma once
#include "pch.h"
#include "CamiBase.h"

using namespace std;

class CamiSolucio : public CamiBase
{
public:
	CamiSolucio() {}
	CamiSolucio(CamiSolucio& camiSolucio);
	~CamiSolucio() {}

	CamiSolucio* clone() { return new CamiSolucio(*this); }
	std::vector<Coordinate> getCamiCoords() { return m_Coordinates; }
	void addCoordinate(Coordinate coordinate) { m_Coordinates.push_back(coordinate); }

private:
	vector<Coordinate> m_Coordinates;
};
