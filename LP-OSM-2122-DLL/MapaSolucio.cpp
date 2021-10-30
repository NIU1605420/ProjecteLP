#include "MapaSolucio.h"
#include "PuntDeInteresBotigaSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"

using namespace std;

void MapaSolucio::getPdis(std::vector<PuntDeInteresBase*>&pdis)
{
	Coordinate shopCoordinate;
	shopCoordinate.lat = 41.4918606;
	shopCoordinate.lat = 2.1465411;

	Coordinate restaurantCoordinate;
	restaurantCoordinate.lat = 1.4902204;
	restaurantCoordinate.lat = 2.1406477;

	m_InterestPoints.push_back(new PuntDeInteresBotigaSolucio(shopCoordinate, "La Millor Pastisseria", Bakery));
	m_InterestPoints.push_back(new PuntDeInteresRestaurantSolucio(restaurantCoordinate, "El Millor Restaurant", , true));

}
