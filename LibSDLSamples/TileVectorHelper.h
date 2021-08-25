#ifndef TileVectorHelper_H	
#define TileVectorHelper_H
#include <string>
#include <vector>
class TileVectorHelper
{

public:
	TileVectorHelper();
	~TileVectorHelper();
	std::string GetVectorLocationByLatAndLong(double x, double y);
	/*std::vector<std::string> GetVectorsFromFile(std::string FilePath);
	std::string ReadFileToString(std::string FilePath);
	std::vector<std::string> GetVectorsFromString(std::string My_String);
	std::vector<std::string> split(std::string my_str, char delimiter);*/
};
#endif // !TileVectorHelper_H