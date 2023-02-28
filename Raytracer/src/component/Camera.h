#pragma once

#include "Component.h"
#include "..\scene\Ray.h"
#include <vecmath.h>

class Camera : public Component
{
private:
	vec3f m_position;
	vec3f m_eye;
	vec3f m_up;
	float m_aspectRatio;
	float m_fov;
	
	mat3f inverseViewMatrix;

public:
	void SetPosition(const vec3f& pos)
	{
		m_position = pos;
	}

	void SetViewDir(const vec3f& eye)
	{
		this->m_eye = eye;
	}

	void SetUpDir(const vec3f& up)
	{
		this->m_up = up;
	}

	void RayThrough(Ray& ray, double x, double y) const;

	void GetCameraToWorld();

	Camera();

public:
	COMPONENT_DECLARATION(Camera)
};