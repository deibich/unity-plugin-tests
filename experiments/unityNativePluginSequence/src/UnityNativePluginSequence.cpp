#include <memory>
#include <iostream>
#include <string>

#include "IUnityInterface.h"
#include "IUnityLog.h"
#include "IUnityGraphics.h"


static IUnityInterfaces *s_UnityInterfaces {};
static IUnityLog *s_UnityLog {};
static IUnityGraphics *s_UnityGraphics {};
static UnityGfxRenderer s_UnityGfxRenderer {};

// We tell Unity, that we need up to eventIdCount eventIds.
static constexpr int s_EventIdCount = 6;

// This is the Id of our first event
static int s_EventIdOffset;

static bool rendererInitialized { false };


static void OnRenderEvent(int eventID)
{

}

static void OnRenderEventAndData(int eventID, void *data)
{

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
                rendererInitialized = true;
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

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API logFromPlugin()
    {
        UNITY_LOG(s_UnityLog, "Log from UnityNativePluginSequence");
    }
}
