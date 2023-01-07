#pragma once

#include <vecmath.h>

class Component
{

};

class Transform : public Component
{
public:
	vec3f position;
	vec3f rotation;
	vec3f scale;
};