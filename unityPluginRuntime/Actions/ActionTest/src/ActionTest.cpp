#include <vector>

#include "Action.h"

enum class CustomActionRenderEventTypes :int 
{
	ACTION_INITIALIZE = 0,
	ACTION_TEARDOWN,
	ACTION_USER_UPDATE,
	CUSTOM_ACTION_RENDER_EVENT_TYPE_COUNT
};

class ActionTest final : public Action
{
public:
	ActionTest();
protected:
	void initialize(void* data) override;
	void teardown() override;
	void customRenderEvent(int eventId, void* data) override;
};

ActionTest::ActionTest()
{
	renderEventIDCount_ = static_cast<int>(CustomActionRenderEventTypes::CUSTOM_ACTION_RENDER_EVENT_TYPE_COUNT);
}

void ActionTest::initialize(void* data)
{
	logger_->log("Action initialize");
}

void ActionTest::teardown()
{
	logger_->log("Action teardown");
}

void ActionTest::customRenderEvent(int eventId, void* data)
{
	logger_->log("Action Renderevent");
}

extern "C"
{
	UNITY_INTERFACE_EXPORT Action* UNITY_INTERFACE_API createAction()
	{
		return new ActionTest();
	}
	UNITY_INTERFACE_EXPORT void  UNITY_INTERFACE_API destroyAction(Action* nativeAction)
	{
		delete nativeAction;
	}
	
	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API getRenderEventIDOffset(Action* action)
	{
		if(action == nullptr)
		{
			return -1;
		}
		return action->getRenderEventIDOffset();
	}
}