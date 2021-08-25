#include <fstream>
#include <algorithm>
#include <sstream>
#include "TileVectorHelper.h"
#include <vector>
#include <SDL_stdinc.h>

TileVectorHelper::TileVectorHelper()
{

}
TileVectorHelper::~TileVectorHelper()
{

}
int long2tilex(double lon, int z)
{
	return (int)(floor((lon + 180.0) / 360.0 * (1 << z)));
}

int lat2tiley(double lat, int z)
{
	double latrad = lat * M_PI / 180.0;
	return (int)(floor((1.0 - asinh(tan(latrad)) / M_PI) / 2.0 * (1 << z)));
}
std::string TileVectorHelper::GetVectorLocationByLatAndLong(double x, double y)
{
	int LongTile = long2tilex(x, 13);
	int LatTile = lat2tiley(y, 13);
	std::string URL = "";
	URL.append("http://192.168.254.101/tile/v1/car/tile(");
	URL.append(std::to_string(LongTile));
	URL.append(",");
	URL.append(std::to_string(LatTile));
	URL.append(",13).mvt");
	return URL;
}