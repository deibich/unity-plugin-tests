
#include "d3d11.h"
#include "d3d11_4.h"
#include "d3d11_3.h"


#include <memory>
#include <iostream>
#include <string>

#include "IUnityInterface.h"
#include "IUnityLog.h"
#include "IUnityGraphics.h"
#include "IUnityGraphicsD3D11.h"

static IUnityInterfaces *s_UnityInterfaces {};
static IUnityLog *s_UnityLog {};
static IUnityGraphics *s_UnityGraphics {};
static UnityGfxRenderer s_UnityGfxRenderer {};
static IUnityGraphicsD3D11 *s_UnityGraphicsD3D11 {};


static ID3D11Device* s_d3d11Device {};
static ID3D11Fence* s_d3d11Fence {};
static ID3D11DeviceContext* s_d3d11Ctx {};
static ID3D11DeviceContext4* s_d3d11Context4 {};



// We tell Unity, that we need up to eventIdCount eventIds.
static constexpr int s_EventIdCount = 6;

// This is the Id of our first event
static int s_EventIdOffset;

static bool rendererInitialized { false };

static void OnResourceEvent(void* data)
{
    D3D11_RESOURCE_DIMENSION rd;
    ID3D11Resource* d3d11Resource;
    UnityRenderBuffer urb = (UnityRenderBuffer)data;
    d3d11Resource = s_UnityGraphicsD3D11->TextureFromRenderBuffer(urb);
    if (d3d11Resource == nullptr)
    {
        return;
    }

    d3d11Resource->GetType(&rd);
    switch (rd)
    {
    case D3D11_RESOURCE_DIMENSION_UNKNOWN:
        UNITY_LOG_ERROR(s_UnityLog, "Resource not known.");
        return;
    case D3D11_RESOURCE_DIMENSION_BUFFER:
    {
        ID3D11Buffer* buff = (ID3D11Buffer*)d3d11Resource;
        D3D11_BUFFER_DESC desc;
        buff->GetDesc(&desc);
        //UNITY_LOG(s_UnityLog, std::to_string(desc.ByteWidth).c_str());
    }
    break;
    case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
    {
        ID3D11Texture1D* tex1 = (ID3D11Texture1D*)d3d11Resource;
        D3D11_TEXTURE1D_DESC desc1;
        tex1->GetDesc(&desc1);
        //UNITY_LOG(s_UnityLog, std::to_string(desc1.Width).c_str());
    }
    break;
    case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
    {
        ID3D11Texture2D* tex2 = (ID3D11Texture2D*)d3d11Resource;
        D3D11_TEXTURE2D_DESC desc2;
        tex2->GetDesc(&desc2);

        //UNITY_LOG(s_UnityLog, std::to_string(desc2.Width).c_str());
    }
    break;
    case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
    {
        ID3D11Texture3D* tex3 = (ID3D11Texture3D*)d3d11Resource;
        D3D11_TEXTURE3D_DESC desc3;
        tex3->GetDesc(&desc3);
        //UNITY_LOG(s_UnityLog, std::to_string(desc3.Width).c_str());
    }
    break;
    }

}

static void OnStartupEvent()
{
    s_d3d11Device = s_UnityGraphicsD3D11->GetDevice();
    ID3D11Device5* device5;
    s_d3d11Device->QueryInterface(__uuidof(ID3D11Device5), (void**)&device5);

    device5->CreateFence(0, D3D11_FENCE_FLAG_SHARED, __uuidof(ID3D11Fence), (void**)&s_d3d11Fence);
    
    s_d3d11Device->GetImmediateContext(&s_d3d11Ctx);
    s_d3d11Ctx->QueryInterface(__uuidof(ID3D11DeviceContext4), (void**)&s_d3d11Context4);
    
}

static void OnTeardownEvent()
{
    s_d3d11Context4 = nullptr;
    if(s_d3d11Ctx != nullptr)
    {
        s_d3d11Ctx->Release();
        s_d3d11Ctx = nullptr;
    }
    s_d3d11Device = nullptr;
}

static void signalFence()
{
    auto logVal = "Fence Val: " + std::to_string(s_d3d11Fence->GetCompletedValue());
    UNITY_LOG(s_UnityLog, logVal.c_str());
    s_d3d11Context4->Signal(s_d3d11Fence, 1);
}

static void waitFence()
{
    s_d3d11Context4->Wait(s_d3d11Fence, 1);
    s_d3d11Context4->Signal(s_d3d11Fence, 0);
}

static void OnRenderEvent(int eventID)
{
    if (!rendererInitialized)
    {
        return;
    }
    if (eventID == s_EventIdOffset)
    {
        OnStartupEvent();
    }
    else if (eventID == s_EventIdOffset + 1)
    {
        OnTeardownEvent();
    }
    else if(eventID == s_EventIdOffset + 3)
    {
        signalFence();
    }
    else if (eventID == s_EventIdOffset + 4)
    {
        waitFence();
    }
}

static void OnRenderEventAndData(int eventID, void *data)
{
    if (!rendererInitialized)
    {
        return;
    }
    if (eventID == s_EventIdOffset + 2)
    {
        OnResourceEvent(data);
    }
 
}

// This callback will be called when graphics device is created, destroyed, reset, etc.
// It is possible to miss the kUnityGfxDeviceEventInitialize event in case plugin is loaded at a later time, when the graphics device is already created.
static void OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
    switch (eventType)
    {
        case kUnityGfxDeviceEventInitialize:
            UNITY_LOG(s_UnityLog, "kUnityGfxDeviceEventInitialize");
			if(!rendererInitialized)
			{
                UNITY_LOG(s_UnityLog, "Initialize Renderer.");
                s_UnityGfxRenderer = s_UnityGraphics->GetRenderer();
                s_EventIdOffset = s_UnityGraphics->ReserveEventIDRange(s_EventIdCount);
                UNITY_LOG(s_UnityLog, ("Offset for event ids is: " + std::to_string(s_EventIdOffset)).c_str());
                if(s_UnityGfxRenderer == kUnityGfxRendererD3D11)
                {
                    s_UnityGraphicsD3D11 = s_UnityInterfaces->Get<IUnityGraphicsD3D11>();
                    rendererInitialized = true;
                }
                else
                {
                    UNITY_LOG(s_UnityLog, "Backend is not D3D11!");
                }
			}
            else
            {
                UNITY_LOG(s_UnityLog, "Renderer was already initialized.");
            }
            break;
        case kUnityGfxDeviceEventShutdown:
            // Gets called multiple times sometimes
            UNITY_LOG(s_UnityLog, "kUnityGfxDeviceEventShutdown");
            rendererInitialized = false;
            break;
        case kUnityGfxDeviceEventBeforeReset:
            UNITY_LOG(s_UnityLog, "kUnityGfxDeviceEventBeforeReset");
            break;
        case kUnityGfxDeviceEventAfterReset:
            UNITY_LOG(s_UnityLog, "kUnityGfxDeviceEventAfterReset");
            break;
        
    }
    // reserves 'count' event IDs. Plugins should use the result as a base index when issuing events back and forth to avoid event id clashes.
}

extern "C" {
    // If exported by a plugin, this function will be called when the plugin is loaded.
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
    {
        if(s_UnityInterfaces != nullptr)
        {
            if(s_UnityLog != nullptr)
            {
                UNITY_LOG_ERROR(s_UnityLog, "Unity tries to load the plugin a seconds time. Which should not happen!\n");
            }
            else
            {
                std::cerr << "Unity tries to load the plugin a second time. Which should not happen!\n";
            }
            return;
        }
        s_UnityInterfaces = unityInterfaces;
        s_UnityLog = s_UnityInterfaces->Get<IUnityLog>();
        if(s_UnityLog == nullptr)
        {
            std::cerr << "Could not retrieve IUnityLog from unityInterfaces.\n";
        }
        else
        {
            UNITY_LOG(s_UnityLog, "UnityNativePluginSequence loaded.");
        }

        s_UnityGraphics = s_UnityInterfaces->Get<IUnityGraphics>();


        if(s_UnityGraphics != nullptr)
        {
            UNITY_LOG(s_UnityLog, "Register Device Event callback for graphicsdevice");
	        s_UnityGraphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);

	        // In case the graphics device was already loaded the Init event is not raised. Do it manually here.
	        OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
        }
    }

    // If exported by a plugin, this function will be called when the plugin is about to be unloaded.
    // Unity unloads the plugin only, when th Editor gets closed!
    // This function des not get called every time for some reason.
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
    {
        if(s_UnityInterfaces == nullptr)
        {
            std::cout << "Unity tries to unload the plugin UnityNativePluginSequence. But it was not loaded.\n";
            return;
        }

        UNITY_LOG(s_UnityLog, "Unload plugin UnityNativePluginSequence.");
        
        s_UnityGraphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);

        s_UnityGraphics = nullptr;
        s_UnityLog = nullptr;
        s_UnityInterfaces = nullptr;
    }    

    UNITY_INTERFACE_EXPORT UnityRenderingEvent UNITY_INTERFACE_API
    GetRenderEventFunc()
    {
        return OnRenderEvent;
    }
    
    UNITY_INTERFACE_EXPORT UnityRenderingEventAndData UNITY_INTERFACE_API
    GetRenderEventAndDataFunc()
    {
        return OnRenderEventAndData;
    }

}
