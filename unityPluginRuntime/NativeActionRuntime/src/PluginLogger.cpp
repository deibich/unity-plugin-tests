#include "PluginLogger.h"

#include "IUnityLog.h"

PluginLogger::PluginLogger(IUnityLog* unityLog) : unityLog_(unityLog)
{
}

void PluginLogger::log(const char* message, const std::source_location location) const
{
	unityLog_->Log(UnityLogType::kUnityLogTypeLog, message, location.file_name(), location.line());
}
