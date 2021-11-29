#pragma once
#include "CamiSolucio.h"
#include "MapaBase.h"
#include "MapaRender.h"

class MapaSolucio : public MapaBase
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
	bool findNameTag(vector<CHILD_NODE> childVector)
	{
		for (int i_Childs = 0; i_Childs < childVector.size(); i_Childs++)
			if (childVector[i_Childs].first == "tag" && childVector[i_Childs].second[0].second == "name")
				return true;
		return false;
	}

private:
	vector<PuntDeInteresBase*> m_InterestPoints;
	vector<CamiBase*> m_BaseWays;
};