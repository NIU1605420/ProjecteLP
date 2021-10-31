#pragma once

#include <string>
#include "Common.h"

using namespace std;

class PuntDeInteresBase {

	private:
		Coordinate m_coord;
		string m_name;

	public:		
		PuntDeInteresBase();
		PuntDeInteresBase(Coordinate coord, string name);
		PuntDeInteresBase(PuntDeInteresBase& interestBasePoint): m_coord(interestBasePoint.m_coord), m_name(interestBasePoint.m_name) {}

		virtual PuntDeInteresBase* clone() { return new PuntDeInteresBase(*this); }
		Coordinate getCoord();
		virtual string getName();
		virtual unsigned int getColor();
		void setName(string name) { m_name = name; }
		void setCoord(Coordinate coordinate) { m_coord = coordinate; }
};