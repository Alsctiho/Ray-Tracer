#pragma once

#include "Component.h"
#include <vecmath.h>

class Camera : public Component
{
private:
	vec3f position;
	vec3f eye;
	vec3f up;

public:
	void SetPosition(const vec3f& pos)
	{
		position = pos;
	}

	void SetViewDir(const vec3f& eye)
	{
		this->eye = eye;
	}

	void SetUpDir(const vec3f& up)
	{
		this->up = up;
	}
};