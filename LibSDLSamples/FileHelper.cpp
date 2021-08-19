#include <fstream>
#include <algorithm>
#include "FileHelper.h"
#include <vector>
FileHelper::FileHelper()
{

}
FileHelper::~FileHelper()
{

}
std::string CleanString(std::string clean)
{
	clean.erase(std::remove(clean.begin(), clean.end(), '('), clean.end());
	clean.erase(std::remove(clean.begin(), clean.end(), ')'), clean.end());
	std::replace(clean.begin(), clean.end(), ' ', ',');
	return clean;
}
std::vector<std::string> FileHelper::GetCoordinatesByFileName(std::string FilePath)
{
	std::vector<std::string> splits;
	
	return splits;
}

std::string FileHelper::ReadFileToString(std::string FilePath)
{
	std::string line;
	std::string retval;
	std::ifstream input_file(FilePath);
	std::string LINESTRINGMATCH = "LINESTRING";
	std::string PARENTHOPEN = "(";
	std::string PARENTHCLOSE = ")";
	if (!input_file.is_open()) {
		return "Failed";
	}
	while (std::getline(input_file, line))
	{
		if (line.size() > 15)
		{
			if (line.find(LINESTRINGMATCH) != std::string::npos)
			{
				unsigned first = line.find(PARENTHOPEN);
				unsigned last = line.find(PARENTHCLOSE);
				std::string clean = line.substr(first, last);
				clean = CleanString(clean);
				retval += clean;
			}
		}
		
	}
	input_file.close();
	
	return retval;
}
