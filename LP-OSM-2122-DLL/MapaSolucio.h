#pragma once
#include "CamiSolucio.h"
#include "MapaBase.h"
#include "MapaRender.h"

class MapaSolucio: public MapaBase
{
public:
	MapaSolucio() {};
	~MapaSolucio();

	void getPdis(std::vector<PuntDeInteresBase*>& pdis);
	void getCamins(std::vector<CamiBase*>& camins);
	void parsejaXmlElements(std::vector<XmlElement>& xmlElements);

	Coordinate getCoordinatesById(string atributs, vector<XmlElement>& xmlelements);
	void initializeCoordinate(Coordinate& coordinate, vector<PAIR_ATTR_VALUE> attributs);
	void initializePuntInteresRestaurant(vector<CHILD_NODE> childVector, PuntDeInteresRestaurantSolucio* puntDeInteresRestaurantSolucio);
	void initializePuntInteresBotiga(vector<CHILD_NODE> childVector, PuntDeInteresBotigaSolucio* puntDeInteresBotigaSolucio);

private:
	vector<PuntDeInteresBase*> m_InterestPoints;
	vector<CamiBase*> m_BaseWays;
};