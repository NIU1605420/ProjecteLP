#pragma once
#include "CamiSolucio.h"
#include "MapaBase.h"

class MapaSolucio: public MapaBase
{
public:
	MapaSolucio() {};
	~MapaSolucio() {};

	void getPdis(std::vector<PuntDeInteresBase*>& pdis);
	void getCamins(std::vector<CamiBase*>& camins) { m_BaseWays.push_back(new CamiSolucio()); }

private:
	vector<PuntDeInteresBase*> m_InterestPoints;
	vector<CamiBase*> m_BaseWays;
};