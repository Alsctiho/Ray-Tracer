#pragma once

#include "../app/Logger.h"
#include <sstream>

class Exception 
{
public:
	template<typename P1, typename ... Param>
	Exception(const P1& p1, const Param& ... param)
	{
		Insert(p1, param ...);
	}

	virtual void LogMessage() const
	{
		RayTracer::error << m_message.str() << RayTracer::endl;
	}

private:
	template<typename P1>
	void Insert(const P1& p1)
	{
		m_message << p1;
	}

	template<typename P1, typename ... Param>
	void Insert(const P1& p1, const Param& ... param)
	{
		Insert(p1);
		Insert(param ...);
	}

protected:
	std::stringstream m_message;
};

class ReadFileException : public Exception
{
public:
	template<typename P1, typename ... Param>
	ReadFileException(const P1& p1, const Param& ... param)
		: Exception(p1, param ...) {}

	virtual void LogMessage() const
	{
		RayTracer::error << "Read File: " << m_message.str() << RayTracer::endl;
	}
};

class ComponentException : public Exception
{
public:
	template<typename P1, typename ... Param>
	ComponentException(const P1& p1, const Param& ... param)
		: Exception(p1, param ...) {}

	virtual void LogMessage() const
	{
		RayTracer::error << "Component: " << m_message.str() << RayTracer::endl;
	}
};