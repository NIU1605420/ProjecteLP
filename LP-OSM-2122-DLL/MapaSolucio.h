#pragma once
#include "MapaBase.h"

class MapaSolucio: public MapaBase
{
public:
	MapaSolucio() {};
	~MapaSolucio() {};

	void getPdis(std::vector<PuntDeInteresBase*>& pdis) {};

private:
	vector<PuntDeInteresBase*> m_InterestPoints;
};