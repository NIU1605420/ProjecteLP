#pragma once
#include "PuntDeInteresBase.h"
#include <string>
using namespace std;

class PuntDeInteresRestaurantSolucio: public PuntDeInteresBase
{
public:
	PuntDeInteresRestaurantSolucio() : m_Inmobile_Assistance(false) {}
	PuntDeInteresRestaurantSolucio(PuntDeInteresRestaurantSolucio& puntDeInteresRestaurantSolucio)
		:PuntDeInteresBase(puntDeInteresRestaurantSolucio.getCoord(), puntDeInteresRestaurantSolucio.getName()), 
		m_Cuisine(puntDeInteresRestaurantSolucio.m_Cuisine),
		m_Inmobile_Assistance(puntDeInteresRestaurantSolucio.m_Inmobile_Assistance) {}
	PuntDeInteresRestaurantSolucio(Coordinate coordinate, string  name, string cuisine, bool inmobileAssistant) 
		:PuntDeInteresBase(coordinate, name), 
		m_Cuisine(cuisine),
		m_Inmobile_Assistance(inmobileAssistant) {}
	~PuntDeInteresRestaurantSolucio() {};

	virtual PuntDeInteresRestaurantSolucio* clone() { return new PuntDeInteresRestaurantSolucio(*this); }
	string getName() { return PuntDeInteresBase::getName(); }
	unsigned int getColor();
	void setCuisine(string cuisine) { m_Cuisine = cuisine; }
	void setInmobileAssistance(bool inmobileAssistance) { m_Inmobile_Assistance = inmobileAssistance; }
private:
	string m_Cuisine;
	bool m_Inmobile_Assistance;
};