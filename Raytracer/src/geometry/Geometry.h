#pragma once

#include "..\component\Component.h"
#include "..\Component\Material.h"

#include <memory>

// builder pattern, component
class Geometry
{
private:
	std::shared_ptr<Material> m_material;

public: 
	Geometry();

	void AddComponent(Component* component);
};