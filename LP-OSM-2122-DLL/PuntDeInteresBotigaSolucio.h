#pragma once
#include "PuntDeInteresBase.h"

using namespace std;

class PuntDeInteresBotigaSolucio: public PuntDeInteresBase
{
public:
	PuntDeInteresBotigaSolucio() {}
	PuntDeInteresBotigaSolucio(PuntDeInteresBotigaSolucio& puntDeInteresBotigaSolucio) 
		:PuntDeInteresBase(puntDeInteresBotigaSolucio.getCoord(), puntDeInteresBotigaSolucio.getName()),
		m_typeOfShop(puntDeInteresBotigaSolucio.m_typeOfShop) {}
	PuntDeInteresBotigaSolucio(Coordinate coordinate, string  name, string typeOfShop) 
		:PuntDeInteresBase(coordinate, name),
		m_typeOfShop(typeOfShop) {}
	~PuntDeInteresBotigaSolucio() {};

	PuntDeInteresBotigaSolucio* clone() { return new PuntDeInteresBotigaSolucio(*this); }
	string getName() { return PuntDeInteresBase::getName(); }
	unsigned int getColor();
	void setTypeOfShop(string typeOfShop) { m_typeOfShop = typeOfShop; }

private:
	string m_typeOfShop;
};