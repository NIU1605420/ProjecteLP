#pragma once
#include "PuntDeInteresBase.h"
using namespace std;



class PuntDeInteresRestaurantSolucio: public PuntDeInteresBase
{
public:
	PuntDeInteresRestaurantSolucio() {};
	~PuntDeInteresRestaurantSolucio() {};

	string getName() { return PuntDeInteresBase::getName(); }
	unsigned int getColor();
private:
	bool m_Cuisine; //Pizza == true && Chinese == false
	bool m_Inmobile_Assistance;
};