#include "Logger.h"
#include "..\Layer\LogLayer.h"

namespace Alice
{
	/*
	* Helper functions
	*/
	Log& Log::internalLog(const std::string& content)
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
		return internalLog(content);
	}

	Log& Log::operator<<(int i)
	{
		return internalLog(std::to_string(i));
	}

	Log& Log::operator<<(double d)
	{
		return internalLog(std::to_string(d));
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
		return internalLog(content);
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
		return internalLog(content);
	}

	void Log::operator<<(Endl endl)
	{
		InternalNewLine();
	}
}