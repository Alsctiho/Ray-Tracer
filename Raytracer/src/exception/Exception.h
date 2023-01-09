#pragma once

#include "../app/Logger.h"
#include <string>

class Exception 
{
public:
	Exception(std::string&& message)
		: m_message(message) {}

	virtual void LogMessage() const
	{
		RayTracer::error << m_message << RayTracer::endl;
	}

protected:
	std::string m_message;
};

class ReadFileException : public Exception
{
public:
	ReadFileException(std::string&& message)
		: Exception(std::move(message)) {}

	virtual void LogMessage() const
	{
		RayTracer::error << "Read File: " << m_message << RayTracer::endl;
	}
};

class ComponentException : public Exception
{
public:
	ComponentException(std::string&& message)
		: Exception(std::move(message)) {}

	virtual void LogMessage() const
	{
		RayTracer::error << "Component: " << m_message << RayTracer::endl;
	}
};