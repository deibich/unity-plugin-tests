#include "RenderAPI/RenderAPI_D3D11.h"

#include "IUnityGraphics.h"
#include "IUnityGraphicsD3D11.h"
#include "IUnityLog.h"

void RenderAPI_D3D11::ProcessDeviceEvent(UnityGfxDeviceEventType unityGfxDeviceEventType, IUnityInterfaces* interfaces)
{
	switch(unityGfxDeviceEventType)
	{
		case kUnityGfxDeviceEventInitialize:
			graphicsInterface_ = interfaces->Get<IUnityGraphicsD3D11>();
			UNITY_LOG(unityLogger_, "RenderAPI_D3D11 initialized");
			break;
		case kUnityGfxDeviceEventShutdown:
			device_ = nullptr;
			graphicsInterface_ = nullptr;
			break;
		case kUnityGfxDeviceEventBeforeReset:
			break;
		case kUnityGfxDeviceEventAfterReset:
			break;
	}
}

RenderAPI_D3D11::RenderAPI_D3D11(IUnityLog* unityLogger) : RenderAPI(unityLogger), device_(nullptr), graphicsInterface_(nullptr)
{
	UNITY_LOG(unityLogger_, "RenderAPI_D3D11 created");
}

RenderAPI_D3D11::~RenderAPI_D3D11()
{
	device_ = nullptr;
	graphicsInterface_ = nullptr;
}
