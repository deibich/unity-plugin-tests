#pragma once

enum class PluginRenderEventTypes :int
{
	RTE_INITIALIZE = 0,
	RTE_TEARDOWN,
	ACTION_REGISTER,
	ACTION_UNREGISTER,

	ActionRenderEventTypes_MAX
};
