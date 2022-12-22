#include "Image.h"
#include "..\Layer\Layer.h"
#include "Application.h"
#include "Logger.h"

#include "GLFW\glfw3.h"
#include <vecmath.h>
#include <iostream>
#include <string>

Image::Image(std::string path)
{
    m_buffer = stbi_load(path.c_str(), (int*)&m_width, (int*)&m_height, (int*)&m_channel, 0);
    PushImageToOpenGl();
}

Image::Image(uint32_t width, uint32_t height, ImageFormat format, const void* data)
	: m_width(width), m_height(height)
{

	if(format == ImageFormat::RGB)
		m_channel = 3;
	else
		m_channel = 4;

	m_buffer = new uint8_t[width * height * m_channel];
	for (int i = 0; i < width * height; ++i)
	{
		m_buffer[i * m_channel] = 0x00; // R
		m_buffer[i * m_channel + 1] = 0xff; // G
		m_buffer[i * m_channel + 2] = 0xff; // B
		if(m_channel == 4)
			m_buffer[i * m_channel + 3] = 0xff; // A
	}

	PushImageToOpenGl();
}

void Image::PushImageToOpenGl()
{
	// Create a OpenGL texture identifier
	glGenTextures(1, &m_imageTexture);
	glBindTexture(GL_TEXTURE_2D, m_imageTexture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if(m_channel == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_buffer);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer);

	stbi_image_free(m_buffer);
}

Image::~Image()
{

}

void Image::Resize(uint32_t width, uint32_t height)
{

}