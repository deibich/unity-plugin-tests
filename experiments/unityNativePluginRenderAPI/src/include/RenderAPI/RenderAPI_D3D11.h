#pragma once
#include "RenderAPI.h"

struct ID3D11Device;
struct IUnityGraphicsD3D11;

class RenderAPI_D3D11 : public RenderAPI
{
public:

	explicit RenderAPI_D3D11(IUnityLog* unityLogger);

    ~RenderAPI_D3D11() override;
    void ProcessDeviceEvent(UnityGfxDeviceEventType unityGfxDeviceEventType, IUnityInterfaces* interfaces) override;

    bool isInitialized() override
    {
        return graphicsInterface_ != nullptr;
    }

	private:
		
        ID3D11Device *device_ {};
        IUnityGraphicsD3D11 *graphicsInterface_ {};
    
};