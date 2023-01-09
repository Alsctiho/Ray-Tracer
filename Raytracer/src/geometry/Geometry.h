#pragma once

#include "..\component\Component.h"
#include "..\component\BoundingBox.h"
#include "..\component\Transform.h"
#include "..\component\Material.h"
#include "..\scene\SceneObject.h"
#include "..\scene\ComponentBundle.h"

#include <memory>

// a boundle of components
class Geometry : public ComponentBundle
{
private:
	Transform* m_transform = nullptr;
	BoundingBox* m_boundingBox = nullptr;
	Material* m_material = nullptr;

public: 
	Geometry();

	Transform& GetTransform()
	{
		if (m_transform == nullptr)
			m_transform = &ComponentBundle::GetComponent<Transform>();

		return *m_transform; 
	}

	Material& GetMaterial()
	{ 
		if (m_material == nullptr)
			m_material = &ComponentBundle::GetComponent<Material>();

		return *m_material;
	}
};