#include <iostream>

#include "PluginHandler.h"

static std::unique_ptr<PluginHandler> s_PluginHandler = std::make_unique<PluginHandler>();

// This callback will be called when graphics device is created, destroyed, reset, etc.
// It is possible to miss the kUnityGfxDeviceEventInitialize event in case plugin is loaded at a later time, when the graphics device is already created.
static void OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
    s_PluginHandler->onGraphicsDeviceEvent(eventType);
}

static void OnRenderEventAndData(int eventID, void* data)
{
    s_PluginHandler->onRenderEventAndData(eventID, data);
}

extern "C"
{
    // If exported by a plugin, this function will be called when the plugin is loaded.
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
    {
        s_PluginHandler->unityPluginLoad(unityInterfaces);
        s_PluginHandler->registerGraphicsDeviceEvent(OnGraphicsDeviceEvent);
    }

    // If exported by a plugin, this function will be called when the plugin is about to be unloaded.
    // Unity unloads the plugin only, when th Editor gets closed!
    // This function des not get called every time for some reason.
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
    {
        s_PluginHandler->unityPluginUnload();
    }

    UNITY_INTERFACE_EXPORT UnityRenderingEventAndData UNITY_INTERFACE_API GetRenderEventAndDataFunc()
    {
        return OnRenderEventAndData;
    }

	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API InitPlugin()
    {
        return 0;
    }

    UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API GetRenderEventIDOffset()
    {
        return s_PluginHandler->getRenderEventIDOffset();
    }
}
