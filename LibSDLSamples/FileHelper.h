#ifndef FileHelper_H	
#define FileHelper_H
#include <string>
#include <vector>
class FileHelper
{

public:
	FileHelper();
	~FileHelper();
	std::vector<std::string> GetCoordinatesByFileName(std::string FilePath);
	std::string ReadFileToString(std::string FilePath);
};
#endif // !FileHelper_H