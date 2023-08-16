#pragma once
#include <memory>

// Allowed? 
enum UnityGfxRenderer : int;
enum UnityGfxDeviceEventType : int;

struct IUnityInterfaces;
struct IUnityLog;

class RenderAPI
{
public:
	static std::shared_ptr<RenderAPI> createRenderAPI(UnityGfxRenderer apiType, IUnityInterfaces* interfaces);

	RenderAPI() = delete;
	virtual ~RenderAPI()
	{
		unityLogger_ = nullptr;
	}

	explicit RenderAPI(IUnityLog* unityLogger) : unityLogger_(unityLogger) {}

	// Process general event like initialization, shutdown, device loss/reset etc.
	virtual void ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces) = 0;
	virtual bool isInitialized() = 0;

protected:
	IUnityLog *unityLogger_;
};
