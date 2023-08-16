#include <iostream>
#include <string>
#include "IUnityInterface.h"
#include "IUnityLog.h"
#include "IUnityRenderingExtensions.h"


static IUnityInterfaces* s_UnityInterfaces {};
static IUnityLog* s_UnityLog {};

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
UnityPluginLoad(IUnityInterfaces * unityInterfaces)
{
    if (s_UnityInterfaces != nullptr)
    {
        if (s_UnityLog != nullptr)
        {
            UNITY_LOG_ERROR(s_UnityLog, "Unity tries to load the plugin GfxPluginTest a second time. Which should not happen!\n");
        }
        else
        {
            std::cerr << "Unity tries to load the GfxPluginTest plugin a second time. Which should not happen!\n";
        }
        return;
    }
    s_UnityInterfaces = unityInterfaces;
    s_UnityLog = s_UnityInterfaces->Get<IUnityLog>();
    if (s_UnityLog == nullptr)
    {
        std::cerr << "Could not retrieve IUnityLog from unityInterfaces.\n";
    }
    else
    {
        UNITY_LOG(s_UnityLog, "GfxPluginTest loaded.");
    }
}


// If exported by a plugin, this function will be called when the plugin is about to be unloaded.
// Unity unloads the plugin only, when th Editor gets closed!
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
    if (s_UnityInterfaces == nullptr)
    {
        std::cout << "Unity tries to unload the plugin GfxPluginTest. But it was not loaded.\n";
        return;
    }

    UNITY_LOG(s_UnityLog, "Unload plugin GfxPluginTest.");
    
    s_UnityLog = nullptr;
    s_UnityInterfaces = nullptr;
}


// Gets called by unity automatically because we have a "GfxPlugin".
// We also can IssueEvent and
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
UnityRenderingExtEvent(UnityRenderingExtEventType event, void* data)
{
    if(s_UnityLog != nullptr)
    {
        if(event >= kUnityRenderingExtEventCount)
        {

            std::string s = "GfxPluginTest ExternalRenderingEent " + std::to_string(event);

            UNITY_LOG(s_UnityLog, s.c_str());
        }
        
    }
    switch (event)
    {
    case kUnityRenderingExtEventBeforeDrawCall:
        // do some stuff
        break;
    case kUnityRenderingExtEventAfterDrawCall:
        // undo some stuff
        break;
    }

}

