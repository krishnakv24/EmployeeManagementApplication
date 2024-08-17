#pragma once

enum class LogLevel
{
	DBUG,
	INFO,
	WARNING,
	ERR,
	CRITICAL
};

class CAppLogger 
{
public:
	static CAppLogger& getInstance();
	void setLevel(LogLevel level);
	void logToFile(const CString& FilePath, const CString& FileName);
	void log(LogLevel level, const CString& message);
	void debug(const CString& message);
	void info(const CString& message);
	void warning(const CString& message);
	void error(const CString& message);
	void critical(const CString& message);

private:
	CAppLogger();
	~CAppLogger();

	CAppLogger(const CAppLogger&) = delete;
	CAppLogger& operator=(const CAppLogger&) = delete;

	LogLevel logLevel = LogLevel::INFO;
	mutex logMutex;
	ofstream fileStream;
	bool logToFileEnabled = false;

	CString getCurrentTime();
	CString logLevelToString(LogLevel level);
};

#define LOG_DEBUG(msg) CAppLogger::getInstance().debug(msg)
#define LOG_INFO(msg) CAppLogger::getInstance().info(msg)
#define LOG_WARNING(msg) CAppLogger::getInstance().warning(msg)
#define LOG_ERROR(msg) CAppLogger::getInstance().error(msg)
#define LOG_CRITICAL(msg) CAppLogger::getInstance().critical(msg)

