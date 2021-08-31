#include <fstream>
#include <algorithm>
#include <sstream>
#include "FileHelper.h"
#include <vector>
#include <vtzero/vector_tile.hpp>
#include <clara.hpp>
#include "VTZeroUtils.h"
FileHelper::FileHelper()
{

}
FileHelper::~FileHelper()
{

}
class geom_handler {

	std::string output{};

public:
	std::string result()
	{
		return output;
	}
	void points_begin(const uint32_t /*count*/) const noexcept {
	}

	static void points_point(const vtzero::point point) {
		//std::cout << "      POINT(" << point.x << ',' << point.y << ")\n";
	}

	void points_end() const noexcept {
	}

	void linestring_begin(const uint32_t count) {
		output = "      LINESTRING[count=";
		output += std::to_string(count);
		output += "](";
	}

	void linestring_point(const vtzero::point point) {
		output += std::to_string(point.x);
		output += ' ';
		output += std::to_string(point.y);
		output += ',';
	}

	void linestring_end() {
		if (output.empty()) {
			return;
		}
		if (output.back() == ',') {
			output.resize(output.size() - 1);
		}
		output += ")\n";
		//std::cout << output;
	}

	void ring_begin(const uint32_t count) {
		output = "      RING[count=";
		output += std::to_string(count);
		output += "](";
	}

	void ring_point(const vtzero::point point) {
		output += std::to_string(point.x);
		output += ' ';
		output += std::to_string(point.y);
		output += ',';
	}

	void ring_end(const vtzero::ring_type rt) {
		if (output.empty()) {
			return;
		}
		if (output.back() == ',') {
			output.back() = ')';
		}
		switch (rt) {
		case vtzero::ring_type::outer:
			output += "[OUTER]\n";
			break;
		case vtzero::ring_type::inner:
			output += "[INNER]\n";
			break;
		default:
			output += "[INVALID]\n";
		}
		//std::cout << output;
	}

}; // class geom_handler
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
std::string GetMVTFileToString(std::string FilePath)
{
	std::string Result = "";
	int layer_num = 0;
	int feature_num = 0;
	const auto data = read_file(FilePath);
	vtzero::vector_tile tile{ data };
	while (auto layer = tile.next_layer()) {
		while (auto feature = layer.next_feature())
		{
			/*if (feature.has_id())
			{
				Result += feature.id();
			}
			Result += "\n";
			const char* geomtype = vtzero::geom_type_name(feature.geometry_type());
			Result += " geomtype: " + *geomtype;*/
			
			Result += vtzero::decode_geometry(feature.geometry(), geom_handler{});
			//Result += handler.o
		}
		++layer_num;
	}
	return Result;
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
std::vector<std::string> FileHelper::GetVectors(std::string FilePath)
{
	std::vector<std::string> results;
	std::string ResOfFile = GetMVTFileToString(FilePath);
	std::istringstream is(ResOfFile);
	std::string LINESTRINGMATCH = "LINESTRING";
	std::string PARENTHOPEN = "(";
	std::string PARENTHCLOSE = ")";
	std::string line;
	while (std::getline(is, line))
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
