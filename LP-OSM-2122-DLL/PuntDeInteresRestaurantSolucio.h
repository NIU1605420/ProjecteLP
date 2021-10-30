#pragma once
#include "PuntDeInteresBase.h"
#include <string>
using namespace std;

class PuntDeInteresRestaurantSolucio: public PuntDeInteresBase
{
public:
	PuntDeInteresRestaurantSolucio() {};
	PuntDeInteresRestaurantSolucio(Coordinate coordinate, string  name, string cuisine, bool inmobileAssistant) :PuntDeInteresBase(coordinate, name), m_Cuisine(cuisine), m_Inmobile_Assistance(inmobileAssistant) {}
	~PuntDeInteresRestaurantSolucio() {};

	string getName() { return PuntDeInteresBase::getName(); }
	unsigned int getColor();
private:
	string m_Cuisine;
	bool m_Inmobile_Assistance;
};