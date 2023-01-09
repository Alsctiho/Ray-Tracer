#pragma once

#include "..\component\Component.h"
#include <vecmath.h>

class BoundingBox : public Component
{
public:
	vec3f max;
	vec3f min;

	BoundingBox() : BoundingBox(vec3f(), vec3f()) {};
	BoundingBox(float x1, float y1, float z1, float x2, float y2, float z2)
		: BoundingBox(vec3f(x1, y1, z1), vec3f(x2, y2, z2)) {}
	BoundingBox(vec3f max, vec3f min) { this->max = max; this->min = min; }

	void operator=(const BoundingBox& target);

	// Does this bounding box intersect the target?
	bool intersects(const BoundingBox& target) const;

	// does the box contain this point?
	bool intersects(const vec3f& point) const;

	// This method makes this boundingbox bigger.
	void mergeBoundingBox(const BoundingBox& other)
	{
		this->max = maximum(this->max, other.max);
		this->min = minimum(this->min, other.min);
	}

	vec3f getMid() { return (min + max) / 2; }

	CLASS_DECLARATION(BoundingBox)
};