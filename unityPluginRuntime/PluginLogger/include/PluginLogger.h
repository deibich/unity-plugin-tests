#pragma once

#include <source_location>

#include "IUnityInterface.h"
struct IUnityLog;

class PluginLogger
{
public:
	PluginLogger(IUnityLog* unityLog);

	UNITY_INTERFACE_EXPORT void log(const char* message, const std::source_location location = std::source_location::current()) const;

private:
	IUnityLog* unityLog_{ nullptr };
};
