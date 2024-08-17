#include "stdafx.h"
#include "AppLogger.h"

/*
* This class is essential for managing application logging, providing a centralized and controlled way to record events, errors, and informational messages.
* It ensures that log messages are properly recorded in a file, allowing for persistent and structured logging across the application's lifecycle.
*
* Importance:
*
* 1. Centralized Logging:
*    - The class provides a single point of logging for the entire application, ensuring that all log messages are captured in a consistent format.
*    - This is critical for debugging, monitoring application behavior, and maintaining logs for audit purposes.
*
* 2. Thread-Safe Operations:
*    - The use of `std::mutex` ensures that log operations are thread-safe, preventing race conditions and ensuring that log messages are not interleaved or corrupted when multiple threads attempt to write to the log simultaneously.
*
* 3. File-Based Logging:
*    - Log messages are written to a specified file, allowing for persistent storage of logs that can be reviewed after the application has terminated.
*    - The log file can be used for diagnostics, auditing, and understanding application flow or identifying issues post-mortem.
*
* 4. Log Level Management:
*    - The logger allows setting a log level (e.g., DEBUG, INFO, WARNING, ERROR, CRITICAL) so that only messages of a certain severity are recorded.
*    - This is useful for controlling the verbosity of logs, especially in production environments where excessive logging can lead to performance issues or large log files.
*
* 5. Singleton Pattern:
*    - The `CAppLogger` class is implemented as a singleton, ensuring that only one instance of the logger exists throughout the application's lifecycle.
*    - This guarantees that log management is consistent and avoids potential conflicts from multiple instances trying to manage the same log file.
*
* 6. Flexibility and Extensibility:
*    - The class is designed to be flexible, allowing for easy modifications or extensions, such as adding support for logging to multiple destinations (e.g., console, remote servers).
*    - This ensures that the logger can evolve with the application's needs without requiring significant changes to the core logging mechanism.
*/


CAppLogger::CAppLogger() = default;
CAppLogger::~CAppLogger()
{
	if (fileStream.is_open())
	{
		fileStream.close();
	}
}

CAppLogger& CAppLogger::getInstance()
{
	static CAppLogger instance;
	return instance;
}

void CAppLogger::setLevel(LogLevel level)
{
	logLevel = level;
}

void CAppLogger::logToFile(const CString& FilePath, const CString& FileName)
{
	lock_guard<mutex> lock(logMutex);
	CString strFilePath = FilePath + L"\\" + FileName;
	fileStream.open(CT2A(strFilePath), ios::out | ios::app);
	logToFileEnabled = true;
}

void CAppLogger::log(LogLevel level, const CString& message)
{
	if (level >= logLevel)
	{
		lock_guard<mutex> lock(logMutex);
		CString logMessage;
		logMessage.Format(_T("[%s] %s: %s"), getCurrentTime(), logLevelToString(level), message);

		if (logToFileEnabled && fileStream.is_open())
		{
			if (!(fileStream << CT2A(logMessage) << endl))
			{
				cerr << "Failed to write to log file!" << endl;
			}
		}
	}
}

void CAppLogger::debug(const CString& message)
{
	log(LogLevel::DBUG, message);
}

void CAppLogger::info(const CString& message)
{
	log(LogLevel::INFO, message);
}

void CAppLogger::warning(const CString& message)
{
	log(LogLevel::WARNING, message);
}

void CAppLogger::error(const CString& message)
{
	log(LogLevel::ERR, message);
}

void CAppLogger::critical(const CString& message)
{
	log(LogLevel::CRITICAL, message);
}

CString CAppLogger::getCurrentTime()
{
	time_t now = time(nullptr);
	struct tm timeInfo;
	localtime_s(&timeInfo, &now);
	TCHAR buf[20];
	_tcsftime(buf, sizeof(buf) / sizeof(TCHAR), _T("%Y-%m-%d %H:%M:%S"), &timeInfo);
	return CString(buf);
}

CString CAppLogger::logLevelToString(LogLevel level)
{
	switch (level)
	{
	case LogLevel::DBUG: return _T("DEBUG");
	case LogLevel::INFO: return _T("INFO");
	case LogLevel::WARNING: return _T("WARNING");
	case LogLevel::ERR: return _T("ERROR");
	case LogLevel::CRITICAL: return _T("CRITICAL");
	default: return _T("UNKNOWN");
	}
}
