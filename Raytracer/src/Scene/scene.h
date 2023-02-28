#pragma once

#include "SceneObject.h"
#include "ComponentBundle.h"

#include "..\geometry\Geometry.h"
#include "..\component\Camera.h"

#include <map>
#include <memory>

class Scene
{
public:
	const std::vector<std::shared_ptr<ComponentBundle>>& GetCameras()
	{
		return m_cameras;
	}

	const Camera& GetCameraSingle()
	{
		return m_cameras[0]->GetComponent<Camera>();
	}

	void SetCamera(std::shared_ptr<ComponentBundle> camera)
	{
		m_cameras.emplace_back(camera);
	}

	void Add(std::shared_ptr<ComponentBundle> obj)
	{
		m_objects.emplace_back(obj);
	}

private:
	std::vector<std::shared_ptr<ComponentBundle>> m_cameras;
	std::vector<std::shared_ptr<ComponentBundle>> m_objects;
};