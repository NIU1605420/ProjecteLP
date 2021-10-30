#pragma once
#include "PuntDeInteresBase.h"

using namespace std;

/*	The objective of creating the Enum Shop is not having Magic numbers;	*/
enum Shop
	{
		SuperMarket = 0,
		Tobacco,
		Bakery
};

class PuntDeInteresBotigaSolucio: public PuntDeInteresBase
{
public:
	PuntDeInteresBotigaSolucio() {}
	PuntDeInteresBotigaSolucio(Coordinate coordinate, string  name, Shop typeOfShop) :PuntDeInteresBase(coordinate, name), m_typeOfShop(typeOfShop) {}
	~PuntDeInteresBotigaSolucio() {};

	string getName() { return PuntDeInteresBase::getName(); }
	unsigned int getColor();
private:
	Shop m_typeOfShop;
};