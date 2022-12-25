#include "Read.h"
#include <string>
#include <fstream>
#include <algorithm>

using RayTracer::log;
using RayTracer::endl;

std::shared_ptr<Scene> SceneReader::ReadScene(const std::string& filename)
{
	std::ifstream file{ filename.c_str() };
	if (!file.is_open()) {
		throw ReadFileException(std::string("Cannot open scene file ") + filename);
	}

	try
	{
		return ReadScene(file);
	}
	catch (ReadFileException& rfe)
	{
		throw rfe;
	}
}

std::shared_ptr<Scene> SceneReader::ReadScene(std::istream& file)
{
	std::shared_ptr<Scene> ret = std::make_shared<Scene>();

	std::string space_delimiter = " ";
	std::string comment_delimiter = "//";
	std::string assignment_delimiter = "=";

	// Extract the file header.
	std::string header;
	std::getline(file, header);

	std::string format = header.substr(0, header.find(space_delimiter));
	std::string version = header.substr(header.find(space_delimiter) + 1);

	if(format != "RayTracer")
		throw ReadFileException(std::string("File format incorrect."));

	if(version != "0.1")
		throw ReadFileException(std::string("Version incorrect. The reading version is ") + version);

	// Extract the file content.
	std::string line;
	while (std::getline(file, line))
	{
		// Handle comment
		size_t commentMaker = line.find(comment_delimiter);
		if (commentMaker != std::string::npos)
		{
			line = line.substr(0, line.find(comment_delimiter));
		}

		line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
		log << line << endl;

		if (line.size() == 0)
			continue;


	}

	// Validate the scene.


	return ret;
}