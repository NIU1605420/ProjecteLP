#pragma once

#include "Common.h"
#include <vector>

class CamiBase {
	public:
		virtual CamiBase* clone() = 0;
		virtual std::vector<Coordinate> getCamiCoords() = 0;
};

