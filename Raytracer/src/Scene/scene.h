#pragma once

#include "Camera.h"
#include "..\geometry\Geometry.h"

#include <map>
#include <memory>

class Scene
{
public:
	void SetCamera(std::shared_ptr<Camera> camera)
	{
		m_camera = camera;
	}

	void Add(std::shared_ptr<Geometry> obj)
	{
		objects.push_back(obj);
	}

private:
	std::shared_ptr<Camera> m_camera = nullptr;
	std::vector<std::shared_ptr<Geometry>> objects;
};