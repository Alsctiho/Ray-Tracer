#pragma once

#include <string>

enum LogLevel
{
	Message,
	Warning,
	Error,
};

namespace Alice
{
	class Endl
	{

	};

	class Log
	{
	public:
		Log& operator<<(std::string content);
		void operator<<(Endl endl);
		virtual ~Log() {}

	protected:
		Log& internalLog(LogLevel level ,std::string& content);
		void InternalNewLine();
		bool newLine = true;
	};

	class LogError : public Log
	{
	public:
		LogError& operator<<(std::string content);
		void operator<<(Endl endl);
	};

	class LogWarning : public Log
	{
	public:
		LogWarning& operator<<(std::string content);
		void operator<<(Endl endl);
	};

	extern Log log;
	extern LogError error;
	extern LogWarning warning;
	extern Endl endl;
}
