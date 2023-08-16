#include "RenderAPI/RenderAPI_D3D11.h"

#include "d3d11.h"
#include "IUnityGraphicsD3D11.h"
#include "PluginLogger.h"

RenderAPI_D3D11::RenderAPI_D3D11(IUnityInterfaces* unityInterfaces, PluginLogger* logger) : RenderAPI(logger)
{
	unityGraphics_ = unityInterfaces->Get<IUnityGraphicsD3D11>();
	if(unityGraphics_ == nullptr)
	{
		logger_->log("Could not retrieve IUnityGraphicsD3D11 from UnityInterfaces");
	}
}

RenderAPI_D3D11::~RenderAPI_D3D11()
{
	device_ = nullptr;
	unityGraphics_ = nullptr;
}

void RenderAPI_D3D11::initialize()
{
	if(device_ == nullptr)
	{
		device_ = unityGraphics_->GetDevice();
		if (device_ == nullptr)
		{
			logger_->log("Could not initialize RenderAPI_D3D11");
		}
	}
	else
	{
		logger_->log("RenderAPI_D3D11 was initialized");
	}
}
