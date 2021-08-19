#ifndef FileHelper_H	
#define FileHelper_H
#include <string>
#include <vector>
class FileHelper
{

public:
	FileHelper();
	~FileHelper();
	std::vector<std::string> GetVectorsFromFile(std::string FilePath);
	std::string ReadFileToString(std::string FilePath);
	std::vector<std::string> GetVectorsFromString(std::string My_String);
	std::vector<std::string> split(std::string my_str, char delimiter);
};
#endif // !FileHelper_H