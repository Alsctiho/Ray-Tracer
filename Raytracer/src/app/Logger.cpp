#include "Logger.h"
#include "..\layer\LogLayer.h"

namespace RayTracer
{
	/*
	* Helper functions
	*/
	Log& Log::InternalLog(const std::string& content)
	{
		LogLayer* logger = LogLayer::GetInstance();
		if (logger)
		{
			if (newLine)
			{
				newLine = false;
				logger->NewLine(m_level, content);
			}
			else
			{
				logger->Append(content);
			}
		}
		return *this;
	}

	void Log::InternalNewLine()
	{
		newLine = true;
		LogLayer::GetInstance()->EndLine();
	}

	Log& Log::operator<<(std::string content)
	{
		return InternalLog(content);
	}

	Log& Log::operator<<(int i)
	{
		return InternalLog(std::to_string(i));
	}

	Log& Log::operator<<(double d)
	{
		return InternalLog(std::to_string(d));
	}

	Log& Log::operator<<(vec3f v)
	{
		std::string content;
		content.append("[");
		content.append(std::to_string(v[0]));
		content.append(", ");
		content.append(std::to_string(v[1]));
		content.append(", ");
		content.append(std::to_string(v[2]));
		content.append("]");
		return InternalLog(content);
	}

	Log& Log::operator<<(vec4f v)
	{
		std::string content;
		content.append("[");
		content.append(std::to_string(v[0]));
		content.append(", ");
		content.append(std::to_string(v[1]));
		content.append(", ");
		content.append(std::to_string(v[2]));
		content.append(", ");
		content.append(std::to_string(v[3]));
		content.append("]");
		return InternalLog(content);
	}

	void Log::operator<<(Endl endl)
	{
		InternalNewLine();
	}
}