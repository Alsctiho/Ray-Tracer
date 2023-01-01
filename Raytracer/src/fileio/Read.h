#pragma once

#include "Dictionary.h"

#include "../app/Logger.h"
#include "../scene/Scene.h"

#include <string>
#include <iostream>
#include <memory>

class ReadFileException {
public:
	ReadFileException(std::string message)
		: m_message(message) {}

	void LogMessage() const
	{
		RayTracer::error << m_message << RayTracer::endl;
	}

private:
	std::string m_message;
};

class SceneReader
{
public:
	SceneReader() {}

	std::shared_ptr<Scene> ReadScene(const std::string& filename);
	std::shared_ptr<Scene> ReadScene(std::istream& file);
	void ParseCamera(std::vector<std::string>::iterator& iter, std::vector<std::string>& lines, Camera* scene);
	void ParseGeometry(std::vector<std::string>::iterator& iter, std::vector<std::string>& lines, Geometry* geometry);

private:
	Dictionary dict;

	vec3f GetVectorField(std::string vector);
};