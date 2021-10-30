#pragma once
#include "PuntDeInteresBase.h"
using namespace std;

enum Cuisine
{
	Default = -1,
	Pizza,
	Chinese
};


class PuntDeInteresRestaurantSolucio: public PuntDeInteresBase
{
public:
	PuntDeInteresRestaurantSolucio() {};
	PuntDeInteresRestaurantSolucio(Coordinate coordinate, string name, Cuisine cuisine, bool InmobilAssistant) : PuntDeInteresBase(coordinate, name), m_Cuisine(cuisine), m_Inmobile_Assistance(InmobilAssistant) {}
	~PuntDeInteresRestaurantSolucio() {};

	string getName() { return PuntDeInteresBase::getName(); }
	unsigned int getColor();
private:
	Cuisine m_Cuisine; 
	bool m_Inmobile_Assistance;
};