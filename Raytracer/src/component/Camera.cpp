#include "Camera.h"

COMPONENT_DEFINITION(Component, Camera)

Camera::Camera()
{
	m_aspectRatio = 0.0;
	m_fov = 90.0;
}

void Camera::RayThrough(Ray& ray, double x, double y) const
{
	// Normalized Device Coordinates [-1, 1)
	// screen space
	x = (2 * x - 1) * m_aspectRatio * tan(m_fov / 2 * PI / 180); // m_aspectRatio
	y = (1 - 2 * y) * tan(m_fov / 2 * PI / 180);

	ray = Ray(inverseViewMatrix * vec3f(0.0, 0.0, 0.0), inverseViewMatrix * vec3f(x, y, -1).normalize());
}

void Camera::GetCameraToWorld()
{

}
