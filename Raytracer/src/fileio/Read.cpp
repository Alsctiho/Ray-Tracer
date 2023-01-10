#include "Read.h"

#include "..\scene\SceneObject.h"
#include "..\Component\Camera.h"
#include "..\geometry\Box.h"

#include <regex>
#include <string>
#include <fstream>
#include <algorithm>

std::string dot_delimiter = ".";
std::string comma_delimiter = ",";
std::string space_delimiter = " ";
std::string comment_delimiter = "//";
std::string assignment_delimiter = "=";
std::string open_bracket_delimiter = "{";
std::string close_bracket_delimiter = "}";

using vs = std::vector<std::string>;

double SceneReader::GetScaleField(std::string scale)
{
	try
	{
		return std::stod(scale);
	}
	catch (const std::invalid_argument&)
	{
		throw ReadFileException("Invalid argument at parsing scale(" + scale + ")");
	}
}

vec3f SceneReader::GetVectorField(std::string vector)
{
	vec3f ret;
	
	std::regex regex(comma_delimiter);

	std::sregex_token_iterator it{ vector.begin(), vector.end(), regex, -1 };
	std::vector<std::string> tokens{ it, {} };

	if(tokens.size() != 1 && tokens.size() != 3)
	{
		throw ReadFileException("Vector field failed");
	}
	
	try
	{
		if (tokens.size() == 1)
		{
			float tempf = std::stof(tokens[0]);
			ret = vec3f(tempf, tempf, tempf);
		}
		else
		{
			ret[0] = std::stof(tokens[0]);
			ret[1] = std::stof(tokens[1]);
			ret[2] = std::stof(tokens[2]);
		}
	}
	catch (const std::invalid_argument&)
	{
		throw ReadFileException("Invalid argument at parsing vec3f(" + vector + ")");
	}
	
	return ret;
}

std::shared_ptr<Scene> SceneReader::ReadScene(const std::string& filename)
{
	try
	{
		std::string format = filename.substr(filename.find_last_of(dot_delimiter) + 1);
		if (format != "ray")
			throw ReadFileException("Not ray format ", filename);

		std::ifstream file{ filename };
		if (!file.is_open())
		{
			throw ReadFileException("Cannot open scene file ", filename);
		}

		return ReadScene(file);
	}
	catch (Exception& rfe)
	{
		rfe.LogMessage();
	}

	return {};
}

std::shared_ptr<Scene> SceneReader::ReadScene(std::istream& file)
{
	std::shared_ptr<Scene> ret = std::make_shared<Scene>();
	Scene* scene = ret.get();

	// Extract the file header.
	std::string header;
	std::getline(file, header);

	std::string format = header.substr(0, header.find(space_delimiter));
	std::string version = header.substr(header.find(space_delimiter) + 1);

	if(format != "RayTracer")
		throw ReadFileException(std::string("File format incorrect."));

	if(version != "0.1")
		throw ReadFileException("Version incorrect. The reading version is ", version);

	// Extract the file content.
	std::string line;
	std::vector<std::string> lines;

	// Handle comment
	while (std::getline(file, line))
	{
		size_t commentMarker = line.find(comment_delimiter);
		if (commentMarker != std::string::npos)
		{
			line = line.substr(0, commentMarker);
		}
		line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

		if (line.size() == 0)
			continue;

		lines.push_back(line);
	}

	for (auto lineIter = lines.begin(); lineIter != lines.end(); ++lineIter)
	{
		//RayTracer::log << *lineIter << RayTracer::endl;

		size_t dotMarker = lineIter->find_first_of(dot_delimiter);
		size_t assignmentMarker = lineIter->find(assignment_delimiter);
		size_t openBracketMarker = lineIter->find(open_bracket_delimiter);

		// Parse method.
		if (dotMarker != std::string::npos)
		{
			std::string objectName = lineIter->substr(0, dotMarker);

			if (dict.Contains(objectName))
			{
				dict.Get(objectName)->ParseObjectMethod(lineIter, lines);
			}
		}
		// Parse object defination.
		else if (assignmentMarker != std::string::npos)
		{
			std::string objectType = lineIter->substr(0, assignmentMarker);
			std::string objectName = lineIter->substr(assignmentMarker + 1, openBracketMarker);

			if (objectType == "" || objectName == "")
				throw ReadFileException("Parsing Error");

			

			if (objectType == "Camera")
			{
				std::shared_ptr<SceneObject> object = std::make_shared<SceneObject>();
				object->AddComponent<Camera>();
				scene->SetCamera(object);
				Camera& camera = object->GetComponent<Camera>();
				std::shared_ptr<CameraObject> cameraObj = std::make_shared<CameraObject>(objectName, &camera);
				dict.Add(objectName, cameraObj);
				ParseCamera(lineIter, lines, &camera);
			}
			else if (objectType == "Box")
			{
				std::shared_ptr<Geometry> box = std::make_shared<Box>();
				scene->Add(box);

				std::shared_ptr<GeometryObject> geometryObject = std::make_shared<GeometryObject>(objectName, box.get());
				dict.Add(objectName, geometryObject);

				ParseGeometry(lineIter, lines, box.get());
			}
			else
			{

			}
		}
	}

	// Validate the scene.
	if(scene->GetCameras().size() <= 0)
		throw ReadFileException("Camera number not enough");

	return ret;
}

void SceneReader::ParseCamera(vs::iterator& iter, vs& lines, Camera* camera)
{
	iter++; // Skip the defination.
	size_t closeBarcketMarker;
	while (true)
	{
		closeBarcketMarker = iter->find(close_bracket_delimiter);
		if (closeBarcketMarker != std::string::npos)
		{
			iter++; // Skip the close bracket.
			break;
		}

		size_t assignmentMarker = iter->find(assignment_delimiter);
		std::string fieldName = iter->substr(0, assignmentMarker);
		std::string fieldVector = iter->substr(assignmentMarker + 1);

		if (fieldName == "position")
		{
			vec3f position = GetVectorField(fieldVector);
			camera->SetPosition(position);
		}
		else if (fieldName == "viewdir")
		{
			vec3f viewdir = GetVectorField(fieldVector);
			camera->SetViewDir(viewdir);
		}
		else if (fieldName == "updir")
		{
			vec3f updir = GetVectorField(fieldVector);
			camera->SetUpDir(updir);
		}
		else
		{
			throw ReadFileException("No a field for camera in line: " + *iter);
		}

		iter++;
	}
}

void SceneReader::ParseGeometry(vs::iterator& iter, vs& lines, Geometry* geometry)
{
	iter++; // Skip the defination.
	size_t closeBarcketMarker;
	while (true)
	{
		closeBarcketMarker = iter->find(close_bracket_delimiter);
		if (closeBarcketMarker != std::string::npos)
		{
			iter++; // Skip the close bracket.
			break;
		}

		size_t assignmentMarker = iter->find(assignment_delimiter);
		std::string fieldName = iter->substr(0, assignmentMarker);
		std::string fieldVector = iter->substr(assignmentMarker + 1);

		if (fieldName == "position")
		{
			geometry->GetTransform().position = GetVectorField(fieldVector);
		}
		else if (fieldName == "rotation")
		{
			geometry->GetTransform().rotation = GetVectorField(fieldVector);
		}
		else if (fieldName == "scale")
		{
			geometry->GetTransform().scale = GetVectorField(fieldVector);
		}
		else if (fieldName == "material")
		{
			iter++;
			ParseMaterial(iter, lines, &geometry->GetMaterial());
		}
		else
		{
			throw ReadFileException("No a field for geometry in line: " + *iter);
		}

		iter++;
	}
}

void SceneReader::ParseMaterial(vs::iterator& iter, vs& lines, Material* material)
{
	iter++; // Skip the defination.
	size_t closeBarcketMarker;
	while (true)
	{
		// TODO: might skill whole string if two "}" stacks in the same line, buggy.
		closeBarcketMarker = iter->find(close_bracket_delimiter);
		if (closeBarcketMarker != std::string::npos)
		{
			iter++; // Skip the close bracket.
			break;
		}

		size_t assignmentMarker = iter->find(assignment_delimiter);
		std::string fieldName = iter->substr(0, assignmentMarker);
		std::string fieldVector = iter->substr(assignmentMarker + 1);

		if (fieldName == "ke")
		{
			vec3f ke = GetVectorField(fieldVector);
			material->ke = ke;
		}
		else if (fieldName == "ka")
		{
			vec3f ka = GetVectorField(fieldVector);
			material->ka = ka;
		}
		else if (fieldName == "ks")
		{
			vec3f ks = GetVectorField(fieldVector);
			material->ks = ks;
		}
		else if (fieldName == "kd")
		{
			vec3f kd = GetVectorField(fieldVector);
			material->kd = kd;
		}
		else if (fieldName == "kr")
		{
			vec3f kr = GetVectorField(fieldVector);
			material->kr = kr;
		}
		else if (fieldName == "kt")
		{
			vec3f kt = GetVectorField(fieldVector);
			material->kt = kt;
		}
		else if (fieldName == "shininess")
		{
			double shininess = GetScaleField(fieldVector);
			material->shininess = shininess;
		}
		else
		{
			throw ReadFileException("No a field for geometry in line: " + *iter);
		}

		iter++;
	}
}