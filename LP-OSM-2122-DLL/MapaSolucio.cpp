#include "MapaSolucio.h"
#include "pch.h"
#include "PuntDeInteresBotigaSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"

using namespace std;

MapaSolucio::~MapaSolucio()
{
	for (auto it = m_BaseWays.begin(); it != m_BaseWays.end(); it++)
		delete (*it);
	for (auto it = m_InterestPoints.begin(); it != m_InterestPoints.end(); it++)
		delete (*it);
}

void MapaSolucio::getPdis(std::vector<PuntDeInteresBase*>& pdis)
{

	//Coordinate coordinate;
	//coordinate.lat = 41.4918606;
	//coordinate.lon = 2.1465411;
	//pdis.push_back(new PuntDeInteresBotigaSolucio(coordinate, "La Millor Pastisseria", "bakery"));

	//coordinate.lat = 41.4902204;
	//coordinate.lon = 2.1406477;
	//pdis.push_back(new PuntDeInteresRestaurantSolucio(coordinate, "El Millor Restaurant", "regional", true));
	pdis.clear();

	for (auto it = m_InterestPoints.begin(); it != m_InterestPoints.end(); it++)
	{
		pdis.push_back((*it)->clone());
	}
}

void MapaSolucio::getCamins(std::vector<CamiBase*>& camins)
{
	//CamiSolucio* camiSolucio = new CamiSolucio();
	//(*camiSolucio).getCamiCoords();
	//camins.push_back(camiSolucio);
	camins.clear();

	for (auto it = m_BaseWays.begin(); it != m_BaseWays.end(); it++)
	{
		camins.push_back((*it)->clone());
	}
}

void MapaSolucio::parsejaXmlElements(std::vector<XmlElement>& xmlElements)
{
	for (auto it = m_BaseWays.begin(); it != m_BaseWays.end(); it++)
		delete (*it);
	m_BaseWays.clear();

	for (auto it = m_InterestPoints.begin(); it != m_InterestPoints.end(); it++)
		delete (*it);
	m_InterestPoints.clear();

	Coordinate coordinate;
	for (int i_xmlElements = 0; i_xmlElements < xmlElements.size(); i_xmlElements++)
		if (xmlElements[i_xmlElements].id_element == "node") // Check element
		{
			PuntDeInteresBase* base_InterestPoint;
			initializeCoordinate(coordinate, xmlElements[i_xmlElements].atributs);
			int i_Childs = 0;
			bool found_Childs = false;
			while (i_Childs < xmlElements[i_xmlElements].fills.size() && !found_Childs) // Moving through the Child vector
			{
				if (xmlElements[i_xmlElements].fills[i_Childs].first == "tag")
				{
					if (xmlElements[i_xmlElements].fills[i_Childs].second[1].second == "restaurant") //The next one to begin is the pair value
					{
						PuntDeInteresRestaurantSolucio* restaurant_PointOfInterest = new PuntDeInteresRestaurantSolucio();
						initializePuntInteresRestaurant(xmlElements[i_xmlElements].fills, restaurant_PointOfInterest);
						(*restaurant_PointOfInterest).setCoord(coordinate);
						base_InterestPoint = restaurant_PointOfInterest;
						found_Childs = true;
					}
					else if (xmlElements[i_xmlElements].fills[i_Childs].second[1].second == "shop")
					{
						PuntDeInteresBotigaSolucio* Shop_PointOfInterest = new PuntDeInteresBotigaSolucio();
						initializePuntInteresBotiga(xmlElements[i_xmlElements].fills, Shop_PointOfInterest);
						(*Shop_PointOfInterest).setCoord(coordinate);
						base_InterestPoint = Shop_PointOfInterest;
						found_Childs = true;
					}
				}
				i_Childs++;
			}
			m_InterestPoints.push_back(base_InterestPoint);
		}
		else if (xmlElements[i_xmlElements].id_element == "way")
		{
			bool found_HighWay = false;
			int i_Childs = 0;
			while (!found_HighWay && i_Childs < xmlElements[i_xmlElements].fills.size())
				if (xmlElements[i_xmlElements].fills[i_Childs].first == "tag")
					if (xmlElements[i_xmlElements].fills[i_Childs].second[0].second == "highway")
					{
						found_HighWay == true;
						for (auto it_Ref = xmlElements[i_xmlElements].fills.begin(); it_Ref != xmlElements[i_xmlElements].fills.end(); it_Ref++)
							if ((*it_Ref).first == "nd" && (*it_Ref).second[0].first == "ref")
							{
								CamiSolucio way_Solution;
								coordinate = getCoordinatesById((*it_Ref).second[0].second, xmlElements);
								way_Solution.addCoordinate(coordinate);
								m_BaseWays.push_back(way_Solution.clone());
							}
					}
				else
					i_Childs++;
		}
}

Coordinate MapaSolucio::getCoordinatesById(string atributs, vector<XmlElement>& xmlelements)
{
	Coordinate result_Coordinate;
	bool found_id = false;
	int i_XMLElement = 0;
	while (!found_id && i_XMLElement < xmlelements.size())
	{
		if (xmlelements[i_XMLElement].id_element == "node")
		{
			int i_Attributes = 0;
			while (!found_id && i_Attributes < xmlelements[i_XMLElement].atributs.size())
			{
				if (xmlelements[i_XMLElement].atributs[i_Attributes].first == "id"
					&& xmlelements[i_XMLElement].atributs[i_Attributes].second == atributs)
				{
					found_id = true;
					initializeCoordinate(result_Coordinate, xmlelements[i_XMLElement].atributs);

				}
				i_Attributes++;
			}
		}
		i_XMLElement++;
	}

	if (!found_id)// Only in case is not found
	{
		result_Coordinate.lat = 0.00; 
		result_Coordinate.lon = 0.00;
	}

	return result_Coordinate;
}

void MapaSolucio::initializeCoordinate(Coordinate& coordinate, vector<PAIR_ATTR_VALUE> attributs)
{
	bool found_latitud = false;
	bool found_lat = false;
	bool found_lon = false;
	int i_Latitud = 0;

	while (i_Latitud < attributs.size() && !found_latitud)
	{
		if (attributs[i_Latitud].first == "lat")
		{
			coordinate.lat = stof(attributs[i_Latitud].second); //From string to double
			found_lat = true;
		}
		else if (attributs[i_Latitud].first == "lon")
		{
			coordinate.lon = stof(attributs[i_Latitud].second); 
			found_lon = true;
		}

		if (found_lat && found_lon)
			found_latitud = true;

		i_Latitud++;
	}
}

void MapaSolucio::initializePuntInteresRestaurant(vector<CHILD_NODE> childVector, PuntDeInteresRestaurantSolucio* puntDeInteresRestaurantSolucio)
{
	int i_Childs = 0;
	bool found_Child = false;
	while (!found_Child && i_Childs < childVector.size())
	{
		if (childVector[i_Childs].second[0].second == "cuisine") 
			(*puntDeInteresRestaurantSolucio).setCuisine(childVector[i_Childs].second[1].second);
		else if (childVector[i_Childs].second[0].second == "name")
			(*puntDeInteresRestaurantSolucio).setName(childVector[i_Childs].second[1].second);
		else if (childVector[i_Childs].second[0].second == "wheelchair" && childVector[i_Childs].second[1].second == "yes")
			(*puntDeInteresRestaurantSolucio).setInmobileAssistance(true);
	}
}

void MapaSolucio::initializePuntInteresBotiga(vector<CHILD_NODE> childVector, PuntDeInteresBotigaSolucio* puntDeInteresBotigaSolucio)
{
	int i_Childs = 0;
	bool found_Child = false;
	while (!found_Child && i_Childs < childVector.size())
	{
		if (childVector[i_Childs].second[0].second == "shop") 
			(*puntDeInteresBotigaSolucio).setTypeOfShop(childVector[i_Childs].second[1].second);
		else if (childVector[i_Childs].second[0].second == "name")
			(*puntDeInteresBotigaSolucio).setName(childVector[i_Childs].second[1].second);
	}
}


