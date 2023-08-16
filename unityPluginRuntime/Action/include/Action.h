#pragma once

#include "IUnityInterface.h"
#include "PluginLogger.h"
#include "RenderAPI.h"

class PluginHandler;

class Action
{
public:
	Action() = default;
	virtual ~Action() = default;

	void renderEventAndData(int eventID, void* data)
	{
		if (eventID - renderEventIDOffset_ == 0)
		{
			initialize(data);
		}
		else if (eventID - renderEventIDOffset_ == 1)
		{
			teardown();
		}
		else
		{
			customRenderEvent(eventID, data);
		}
	}

	virtual int getRenderEventIDCount() { return renderEventIDCount_; }
	virtual int getRenderEventIDOffset() { return renderEventIDOffset_; }
	virtual int getAboveValidRenderEventID() { return aboveValidRenderEventID_; }

	virtual bool isValidEventID(int eventID) { return eventID < aboveValidRenderEventID_ && eventID >= renderEventIDOffset_; }

	void runtimeInitialize(int renderEventIdOffset, PluginLogger* logger, RenderAPI* renderAPI)
	{
		renderEventIDOffset_ = renderEventIdOffset;
		aboveValidRenderEventID_ = renderEventIdOffset + renderEventIDCount_;
		logger_ = logger;
		renderAPI_ = renderAPI;
		isRegistered_ = true;
	}

	void runtimeTearDown()
	{

		logger_ = nullptr;
		renderAPI_ = nullptr;
		isRegistered_ = false;
	}

protected:
	virtual void initialize(void* data) = 0;
	virtual void teardown() = 0;
	virtual void customRenderEvent(int eventId, void* data) = 0;

	bool isRegistered_{ false };

	int renderEventIDOffset_{ 0 };
	int renderEventIDCount_{ 0 };
	int aboveValidRenderEventID_{ 0 };

	PluginLogger* logger_{ nullptr };
	RenderAPI* renderAPI_{ nullptr };
};

extern "C"
{
	UNITY_INTERFACE_EXPORT Action* UNITY_INTERFACE_API createAction();
	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API getRenderEventIDOffset(Action* nativeAction);
	UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API destroyAction(Action* nativeAction);
}
