#pragma once

#include <string>
#include "Common.h"

class PuntDeInteresBase {

	private:
		Coordinate m_coord;
		std::string m_name;

	public:		
		PuntDeInteresBase();
		PuntDeInteresBase(Coordinate coord, std::string name);

		virtual std::string getName();
		Coordinate getCoord();
		virtual unsigned int getColor();
		void setName(std::string name) { m_name = name; }
		void setCoord(Coordinate coordinate) { m_coord = coordinate; }
};