#pragma once

#include "..\component\Component.h"
#include "..\component\BoundingBox.h"
#include "..\component\Transform.h"
#include "..\component\Material.h"
#include "..\scene\SceneObject.h"
#include "..\scene\ComponentBundle.h"
#include "..\scene\Scene.h"

#include <memory>

// a boundle of components
class Geometry : public ComponentBundle
{
private:
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<BoundingBox> m_boundingBox;
	std::shared_ptr<Material> m_material;

public: 
	Geometry();

	Transform& GetTransform()
	{
		return *m_transform; 
	}

	Material& GetMaterial()
	{ 
		return *m_material;
	}
};