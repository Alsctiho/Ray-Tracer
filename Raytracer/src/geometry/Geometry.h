#pragma once

#include "..\scene\SceneObject.h"
#include "..\component\Component.h"
#include "..\scene\BoundingBox.h"
#include "..\component\Material.h"

#include <memory>

// a boundle of components
class Geometry : public SceneObject
{
private:
	Transform m_transform;
	BoundingBox m_boundingBox;
	Material m_material;

public: 
	Geometry();

	Transform& GetTransform() { return m_transform; }
	Material& GetMaterial() { return m_material; }
};