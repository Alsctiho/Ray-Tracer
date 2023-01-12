#pragma once

#include "../scene/Scene.h"
#include "../imageio/Image.h"

class RayTracer
{
public:
	void Render();
	void TraceLines(int start, int stop);
	void TracePixel(int i, int j);

	vec3f Trace(Scene* scene, int i, int j, int buffer_width, int buffer_height);

	void SetImage(Image* image)
	{
		m_image = image;
	}

	void SetScene(Scene* scene)
	{
		m_scene = scene;
	}

private:
	// RayTracer doesnt own the scene and image.
	Scene* m_scene;
	Image* m_image = nullptr;
};