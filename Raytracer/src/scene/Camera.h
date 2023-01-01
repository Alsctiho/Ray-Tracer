#pragma once

#include <vecmath.h>

class Camera
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