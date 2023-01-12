#pragma once

#include "Component.h"
#include <vecmath.h>

class Transform : public Component
{
public:
	vec3f position;
	vec3f rotation;
	vec3f scale;

	mat4f transform;
	mat4f inverse;

public:
	COMPONENT_DECLARATION(Transform)
};