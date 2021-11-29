#pragma once

#include "pch.h"
#include "Common.h"
#include <fstream>

class Util {
	private:
		static const std::string m_logFileName;
		static double m_PI;
		static double m_RadiTerraX2;

	public:
		Util();

		static double deg2Rad(double deg);
		static double rad2Deg(double rad);

		static std::pair<std::string, std::string> kvDeTag(std::vector<PAIR_ATTR_VALUE>& atributsTag);
		static void escriuEnMonitor(std::string text);
		
		static double DistanciaHaversine(double lat1, double lon1, double lat2, double lon2);
		static double DistanciaHaversine(Coordinate px1, Coordinate px2);

};



