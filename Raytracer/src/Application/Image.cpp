#include "Image.h"
#include "..\Layer\Layer.h"
#include "Application.h"
#include "Logger.h"

#include "GLFW\glfw3.h"
#include <iostream>
#include <string>

Image::Image(std::string path, ImageFormat format)
{
    m_buffer = stbi_load(path.c_str(), (int*)&m_width, (int*)&m_height, (int*)&m_channel, 0);
	Alice::log << "hello " << std::to_string(m_width) << Alice::endl;
	Alice::log << "hello " << std::to_string(m_height);
	Alice::error << "hello " << std::to_string(m_height) << Alice::endl;
    PushImageToOpenGl();
}

Image::Image(uint32_t width, uint32_t height, ImageFormat format, const void* data)
	: m_width(width), m_height(height), m_channel(3)
{
	m_buffer = new uint8_t[width * height * 3];
	for (int i = 0; i < width * height; ++i)
	{
		m_buffer[i * 3] = 0x00; // R
		m_buffer[i * 3 + 1] = 0xff; // G
		m_buffer[i * 3 + 2] = 0xff; // B
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_buffer);
	stbi_image_free(m_buffer);
}

Image::~Image()
{

}

void Image::Resize(uint32_t width, uint32_t height)
{

}