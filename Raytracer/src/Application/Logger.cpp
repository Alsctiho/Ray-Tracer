#include "Logger.h"
#include "..\Layer\LogLayer.h"

namespace Alice
{
	Log& Log::operator<<(std::string content)
	{
		return internalLog(Message, content);
	}

	Log& Log::internalLog(LogLevel level, std::string& content)
	{
		LogLayer* logger = LogLayer::GetInstance();
		if (logger)
		{
			if (newLine)
			{
				newLine = false;
				logger->NewLine(level, content);
			}
			else
			{
				logger->Append(content);
			}
		}
		return *this;
	}

	void Log::operator<<(Endl endl)
	{
		InternalNewLine();
	}

	void Log::InternalNewLine()
	{
		newLine = true;
		LogLayer::GetInstance()->EndLine();
	}

	LogError& LogError::operator<<(std::string content)
	{
		return dynamic_cast<LogError&>(internalLog(Warning, content));
	}

	void LogError::operator<<(Endl endl)
	{
		InternalNewLine();
	}

	LogWarning& LogWarning::operator<<(std::string content)
	{
		return dynamic_cast<LogWarning&>(internalLog(Warning, content));
	}

	void LogWarning::operator<<(Endl endl)
	{
		InternalNewLine();
	}
}