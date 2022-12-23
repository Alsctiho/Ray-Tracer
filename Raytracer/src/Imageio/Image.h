#pragma once

#include "stb/stb_image.h"
#include "glfw/glfw3.h"
#include <string>
enum class ImageFormat
{
	RGB,
	RGBA,
};

class Image
{
public:
	Image(std::string path);
	Image(uint32_t width, uint32_t height, ImageFormat format, const void* data = nullptr);
	~Image();

	void Resize(uint32_t width, uint32_t height);

	unsigned char* GetBuffer() { return m_buffer; }
	uint32_t GetWidth() const { return m_width; }
	uint32_t GetHeight() const { return m_height; }
	GLuint GetDescriptorSet() const { return m_imageTexture; }

private:
	void PushImageToOpenGl();

private:
	GLuint m_imageTexture = 0;
	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_channel;

	unsigned char* m_buffer;
};