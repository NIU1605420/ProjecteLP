#include "pch.h"
#include "CamiSolucio.h"

vector<Coordinate> CamiSolucio::getCamiCoords()
{
	Coordinate c;

	m_coordinates.resize(0);

	c.lat = 41.4928803;
	c.lon = 2.1452381;

	m_coordinates.push_back(c);

	c.lat = 41.4929072;
	c.lon = 2.1452474;

	m_coordinates.push_back(c);

	c.lat = 41.4933070;
	c.lon = 2.1453852;


	m_coordinates.push_back(c);

	c.lat = 41.4939882;
	c.lon = 2.1456419;

	m_coordinates.push_back(c);

	return m_coordinates;


}

