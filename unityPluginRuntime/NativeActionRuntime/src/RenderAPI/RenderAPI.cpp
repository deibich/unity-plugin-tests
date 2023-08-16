#include "RenderAPI.h"
#include "IUnityGraphics.h"

#include "RenderAPI/RenderAPI_D3D11.h"

std::unique_ptr<RenderAPI> RenderAPI::createRenderAPI(UnityGfxRenderer unityGfxRenderer, IUnityInterfaces* unityInterfaces, PluginLogger *logger)
{
	switch( unityGfxRenderer )
	{
		case kUnityGfxRendererD3D11:
			return std::make_unique<RenderAPI_D3D11>(unityInterfaces, logger);
		default:
			break;
	}
	return nullptr;
}

RenderAPI::~RenderAPI() = default;