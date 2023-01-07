#pragma once

#include "SceneObject.h"

#include "..\geometry\Geometry.h"
#include "..\component\Camera.h"

#include <map>
#include <memory>

class Scene
{
public:
	const std::vector<std::shared_ptr<SceneObject>>& GetCameras() 
	{
		return m_cameras;
	}

	void SetCamera(std::shared_ptr<SceneObject> camera)
	{
		m_cameras.push_back(camera);
	}

	void Add(std::shared_ptr<SceneObject> obj)
	{
		m_objects.push_back(obj);
	}

private:
	std::vector<std::shared_ptr<SceneObject>> m_cameras;
	std::vector<std::shared_ptr<SceneObject>> m_objects;
};