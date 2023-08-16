#pragma once
#include <memory>

#include <map>
#include <vector>

#include "IUnityGraphics.h"
#include "IUnityInterface.h"
#include "RenderAPI.h"
#include "PluginLogger.h"

struct IUnityLog;

class Action;


class PluginHandler
{
	public:
        PluginHandler();
        void unityPluginLoad(IUnityInterfaces* unityInterfaces);
        void unityPluginUnload();

        void onGraphicsDeviceEvent(UnityGfxDeviceEventType eventType);
        void onRenderEventAndData(int eventID, void* data);

        void registerGraphicsDeviceEvent(IUnityGraphicsDeviceEventCallback graphicsDeviceEventCallback);
		void unregisterGraphicsDeviceEvent(IUnityGraphicsDeviceEventCallback graphicsDeviceEventCallback);


        int getRenderEventIDOffset() { return renderEventIDOffset_; }

private:
    std::unique_ptr<PluginLogger> logger_{ nullptr };
    std::unique_ptr<RenderAPI>  renderAPI_ { nullptr };

    IUnityInterfaces *unityInterfaces_ { nullptr };
    IUnityGraphics *unityGraphics_ { nullptr };

    int renderEventIDOffset_ { 0 };
    const int renderEventIDCount_;


    void registerAction(Action* action);
    void unregisterAction(Action* action);
    void tearDown();
    
    std::vector<Action*> registeredActions_ {};

};

