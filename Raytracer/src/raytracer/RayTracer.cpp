#include "RayTracer.h"
#include "..\exception\Exception.h"

#include <vecmath.h>

void RayTracer::Render()
{
	if(!m_image)
		throw RayTracerException("No image buffer provide.");

	int height = m_image->GetHeight();
	TraceLines(0, height);

	m_image->PushImageToOpenGl();
}

void RayTracer::TraceLines(int start, int stop)
{
	for (int j = start; j < stop; ++j)
		for (int i = 0; i < m_image->GetWidth(); ++i)
			TracePixel(i, j);
}

void RayTracer::TracePixel(int i, int j)
{
	vec3f col;

	col = Trace(m_scene, i, j, m_image->GetWidth(), m_image->GetHeight());

	unsigned char* pixel = m_image->GetBuffer() + (i + j * m_image->GetWidth()) * m_image->GetChannel();

	pixel[0] = (int)(255.0 * col[0]);
	pixel[1] = (int)(255.0 * col[1]);
	pixel[2] = (int)(255.0 * col[2]);

	if(m_image->GetChannel() == 4)
		pixel[3] = 0xff;
}

// Trace a top-level ray through normalized window coordinates (x,y)
// through the projection plane, and out into the scene.  All we do is
// enter the main ray-tracing method, getting things started by plugging
// in an initial ray weight of (0.0,0.0,0.0) and an initial recursion depth of 0.
vec3f RayTracer::Trace(Scene* scene, int i, int j, int buffer_width, int buffer_height)
{
	return vec3f((double)i / buffer_width, (double) j / buffer_height, 1.0);
}