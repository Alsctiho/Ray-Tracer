#pragma once

#include "Dictionary.h"

#include "../exception/Exception.h"
#include "../scene/Scene.h"

#include <string>
#include <iostream>
#include <memory>


class SceneReader
{
public:
	SceneReader() {}

	using vs = std::vector<std::string>;
	std::shared_ptr<Scene> ReadScene(const std::string& filename);
	std::shared_ptr<Scene> ReadScene(std::istream& file);
	void ParseCamera(vs::iterator& iter, vs& lines, Camera* scene);
	void ParseGeometry(vs::iterator& iter, vs& lines, Geometry* geometry);
	void ParseMaterial(vs::iterator& iter, vs& lines, Material* material);

private:
	Dictionary dict;

	double GetScaleField(std::string scale);
	vec3f GetVectorField(std::string vector);
};