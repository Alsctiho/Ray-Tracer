#include "Geometry.h"

Geometry::Geometry()
{
	m_transform = std::make_shared<Transform>();
	m_boundingBox = std::make_shared<BoundingBox>();
	m_material = std::make_shared<Material>();
}