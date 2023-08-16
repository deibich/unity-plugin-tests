#pragma once
#include <memory>

class PluginLogger;

enum UnityGfxRenderer : int;
struct IUnityInterfaces;

class RenderAPI
{
	public:
		static std::unique_ptr<RenderAPI> createRenderAPI(UnityGfxRenderer unityGfxRenderer, IUnityInterfaces* unityInterfaces, PluginLogger *logger);

		RenderAPI() = delete;

		virtual ~RenderAPI();

		// Use this only on the renderThread
		virtual void initialize() = 0;
	protected:
		RenderAPI(PluginLogger* logger) : logger_(logger) {}

		PluginLogger* logger_;
};
