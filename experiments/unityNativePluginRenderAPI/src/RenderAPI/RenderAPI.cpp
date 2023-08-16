#include "RenderAPI.h"

#include "IUnityInterface.h"
#include "IUnityGraphics.h"

#include "RenderAPI/RenderAPI_D3D11.h"

std::shared_ptr<RenderAPI> RenderAPI::createRenderAPI(UnityGfxRenderer apiType, IUnityInterfaces* interfaces)
{
	switch(apiType)
	{
	case kUnityGfxRendererD3D11:
			return std::make_shared<RenderAPI_D3D11>();
		default:
			break;
	}
}

