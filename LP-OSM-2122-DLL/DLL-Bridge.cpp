#include "pch.h"

#include "MapaRender.h"

// DO NOT TOUCH THIS
extern "C" __declspec(dllexport) void loadOSMData(const char* pathFile) {
	MapaRender* map = MapaRender::instance();
	map->construeixOSM(std::string(pathFile));
}


// DO NOT TOUCH THIS
extern "C" __declspec(dllexport) void renderPois(PoiBridge* (*allocator)(size_t size)) {
	MapaRender* map = MapaRender::instance();
	std::vector<PoiBridge> listPoiBridge = map->renderPois();

	PoiBridge* result = allocator(listPoiBridge.size());
	for (int i = 0; i < listPoiBridge.size(); i++) {
		result[i].i = listPoiBridge[i].i;
		result[i].color = listPoiBridge[i].color;
		result[i].lat = listPoiBridge[i].lat;
		result[i].lon = listPoiBridge[i].lon;
		result[i].title = listPoiBridge[i].title;
	}

}

// DO NOT TOUCH THIS
extern "C" __declspec(dllexport) bool renderWays(int offset, double* (*allocatorLats)(size_t size), double * (*allocatorLons)(size_t size))
{
	MapaRender* map = MapaRender::instance();
	std::vector<WayBridge> listWayBridge = map->renderWays();
	if (offset < 0 || offset >= listWayBridge.size()) {
		return false;
	}

	double* lat = allocatorLats(listWayBridge[offset].size); 
	double* lon = allocatorLons(listWayBridge[offset].size);
	for (int i = 0; i < listWayBridge[offset].size; i++) {
		lat[i] = listWayBridge[offset].lats[i];
		lon[i] = listWayBridge[offset].lons[i];
	}

	return offset + 1 < listWayBridge.size();
}

// DO NOT TOUCH THIS
extern "C" __declspec(dllexport) void shortestPath(int idxFrom, int idxTo, double* (*allocatorLats)(size_t size), double* (*allocatorLons)(size_t size)) 
{

}






