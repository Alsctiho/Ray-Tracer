#include "BoundingBox.h"
#include "..\constant.h"

COMPONENT_DEFINITION(Component, BoundingBox)

void BoundingBox::operator=(const BoundingBox& target)
{
	min = target.min;
	max = target.max;
}

// Does this bounding box intersect the target?
bool BoundingBox::intersects(const BoundingBox& target) const
{
	return ((target.min[0] - Lighting::RAY_EPSILON <= max[0]) && (target.max[0] + Lighting::RAY_EPSILON >= min[0]) &&
		(target.min[1] - Lighting::RAY_EPSILON <= max[1]) && (target.max[1] + Lighting::RAY_EPSILON >= min[1]) &&
		(target.min[2] - Lighting::RAY_EPSILON <= max[2]) && (target.max[2] + Lighting::RAY_EPSILON >= min[2]));
}

// does the box contain this point?
bool BoundingBox::intersects(const vec3f& point) const
{
	return ((point[0] + Lighting::RAY_EPSILON >= min[0]) && (point[1] + Lighting::RAY_EPSILON >= min[1]) && (point[2] + Lighting::RAY_EPSILON >= min[2]) &&
		(point[0] - Lighting::RAY_EPSILON <= max[0]) && (point[1] - Lighting::RAY_EPSILON <= max[1]) && (point[2] - Lighting::RAY_EPSILON <= max[2]));
}