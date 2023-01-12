#include "Geometry.h"

Geometry::Geometry()
{
	m_transform = ComponentBundle::AddComponent<Transform>();
	m_boundingBox = ComponentBundle::AddComponent<BoundingBox>();
	m_material = ComponentBundle::AddComponent<Material>();
}