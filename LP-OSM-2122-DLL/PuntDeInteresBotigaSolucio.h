#pragma once
#include "PuntDeInteresBase.h"

using namespace std;

/*	The objective of creating the Enum Shop is not having Magic numbers;	*/
namespace Shops
{
	enum Shop
	{
		SuperMarket = 0,
		Tobacco,
		Bakery
	};
}

class PuntDeInteresBotigaSolucio: public PuntDeInteresBase
{
public:
	PuntDeInteresBotigaSolucio() {};
	~PuntDeInteresBotigaSolucio() {};

	string getName() { return PuntDeInteresBase::getName(); }
	unsigned int getColor();
private:
	Shops::Shop m_typeOfShop;
};