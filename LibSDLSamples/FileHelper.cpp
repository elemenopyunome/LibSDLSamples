#include <fstream>
#include <algorithm>
#include <sstream>
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
std::vector<std::string> split(std::string my_str, char delimiter)
{
	std::vector<std::string> results;
	std::stringstream s_stream(my_str); 
	while (s_stream.good()) {
		std::string substr;
		getline(s_stream, substr, ','); 
		results.push_back(substr);
	}
	return results;
}
std::string GetOSMNodesOnly(std::string CompleteChunk)
{
	std::string returnresult;
	std::string LAYER1 = "layer: 0";
	std::string LAYER2 = "layer: 1";
	unsigned first = CompleteChunk.find(LAYER1);
	unsigned last = CompleteChunk.find(LAYER2);
	returnresult = CompleteChunk.substr(first, last);
	return returnresult;
}
std::vector<std::string> FileHelper::split(std::string my_str, char delimiter)
{
	std::vector<std::string> results;
	std::stringstream s_stream(my_str);
	while (s_stream.good()) {
		std::string substr;
		getline(s_stream, substr, ',');
		results.push_back(substr);
	}
	return results;
}
std::vector<std::string> FileHelper::GetVectorsFromString(std::string My_String)
{
	std::vector<std::string> results;
	std::istringstream f(My_String);
	std::string line;
	while (std::getline(f, line))
	{
		std::string bla = line;
		results.push_back(bla);
	}
	return results;
}
std::vector<std::string> FileHelper::GetVectorsFromFile(std::string FilePath)
{
	std::vector<std::string> results;
	std::string CompleteString;
	std::string line;
	std::ifstream input_file(FilePath);
	std::string LINESTRINGMATCH = "LINESTRING";
	std::string PARENTHOPEN = "(";
	std::string PARENTHCLOSE = ")";
	if (!input_file.is_open()) {
		
	}
	while (std::getline(input_file, line))
	{
		//retval += line;
		if (line.size() > 15)
		{
			if (line.find(LINESTRINGMATCH) != std::string::npos)
			{
				unsigned first = line.find(PARENTHOPEN);
				unsigned last = line.find(PARENTHCLOSE);
				std::string clean = line.substr(first, last);
				clean = CleanString(clean);
				try
				{
					std::vector<std::string> bla = split(clean, ',');
					if (bla.size() == 4)
					{
						std::string row;
						for (int x = 0; x < bla.size(); x++)
						{
							if (x < 3)
								row += bla[x] + ",";
							else
								row += bla[x];
						}
						results.push_back(row);
					}
				}
				catch (...)
				{

				}
				//retval += clean;
			}
		}
	}
	input_file.close();
	return results;
}

std::string FileHelper::ReadFileToString(std::string FilePath)
{
	std::string CompleteString;
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
		//retval += line;
		if (line.size() > 15)
		{
			if (line.find(LINESTRINGMATCH) != std::string::npos)
			{
				unsigned first = line.find(PARENTHOPEN);
				unsigned last = line.find(PARENTHCLOSE);
				std::string clean = line.substr(first, last);
				clean = CleanString(clean);
				try
				{
					std::vector<std::string> bla = split(clean, ',');
				}
				catch (...)
				{

				}
				retval += clean;
			}
		}
	}
	input_file.close();
	
	return retval;
}
