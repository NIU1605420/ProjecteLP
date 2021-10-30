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

		Coordinate getCoord();
		virtual string getName();
		virtual unsigned int getColor();
};