#pragma once

#include <vecmath.h>
#include <string>
#include <iostream>

enum LogLevel
{
	Message,
	Warning,
	Error,
};

namespace RayTracer
{
	class Endl {};

	class Log
	{
	public:
		Log(LogLevel level) : m_level(level) {}
		Log& operator<<(const std::string& content);
		Log& operator<<(int i);
		Log& operator<<(double d);
		Log& operator<<(const vec3f& v);
		Log& operator<<(const vec4f& v);
		void operator<<(const Endl& endl);
		virtual ~Log() {}

	private:
		LogLevel m_level;
		Log& InternalLog(const std::string& content);
		void InternalNewLine();
		bool newLine = true;
	};

	extern Log log;
	extern Log warning;
	extern Log error;
	extern Endl endl;
}
