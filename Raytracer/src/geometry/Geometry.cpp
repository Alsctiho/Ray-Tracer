#include "Geometry.h"

Geometry::Geometry()
{
	ComponentBundle::AddComponent<Transform>();
	//AddComponent<BoundingBox>();
	//AddComponent<Material>();
}