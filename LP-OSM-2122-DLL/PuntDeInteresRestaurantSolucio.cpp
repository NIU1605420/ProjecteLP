#include "PuntDeInteresRestaurantSolucio.h"
#include "pch.h"

using namespace std;

unsigned int PuntDeInteresRestaurantSolucio::getColor()
{
	if (m_Inmobile_Assistance)
		return 0x251351;
	else if (m_Cuisine == "pizza")
		return 0xA6D9F7;
	else if (m_Cuisine == "chinese")
		return 0x03FCBA;
	else
		return 0xFFA550;
}
