#pragma once
#include "RenderAPI.h"

struct IUnityGraphicsD3D11;
struct ID3D11Device;

class RenderAPI_D3D11 : public RenderAPI
{
	public:
		RenderAPI_D3D11(IUnityInterfaces* unityInterfaces, PluginLogger* logger);

		~RenderAPI_D3D11();
		void initialize() override;

private:
	IUnityGraphicsD3D11 *unityGraphics_ { nullptr };
	ID3D11Device *device_ { nullptr };
};
