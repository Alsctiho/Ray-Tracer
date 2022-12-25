#pragma once

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

class Statement
{
public:
	Statement(std::string statement) {};
	
	std::string name;
	std::string vector;
};

class SceneReader
{
public:
	static std::shared_ptr<Scene> ReadScene(const std::string& filename);
	static std::shared_ptr<Scene> ReadScene(std::istream& file);

private:
	static void ParseCamera(std::istream& file, Scene* scene);
};

