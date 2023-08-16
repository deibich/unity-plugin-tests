add_library(NativeActionRuntime SHARED
	"src/PluginHandler.cpp"
	"src/unity_plugin.cpp"
	"src/RenderAPI/RenderAPI.cpp"
	"src/RenderAPI/RenderAPI_D3D11.cpp"
	"src/PluginLogger.cpp"
 )

target_include_directories(NativeActionRuntime 
	PUBLIC
		"include"
	PRIVATE
		"src/include"
		"interface"
	INTERFACE
		"interface"
)

target_link_libraries(NativeActionRuntime
	PRIVATE
		d3d11.lib
		Action
	PUBLIC
		unityInterfaces
		PluginLogger
)

set_target_properties(NativeActionRuntime PROPERTIES CXX_STANDARD 20)

install(TARGETS NativeActionRuntime DESTINATION ${UNITY_PROJECT_ROOT_DIR}/Assets/${UNITY_ASSETS_SUBDIRECTORY_RUNTIME})
