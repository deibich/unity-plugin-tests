add_library(PluginLogger INTERFACE)

target_include_directories(PluginLogger
	INTERFACE
		"include"
)	


target_link_libraries(PluginLogger
	INTERFACE
		unityInterfaces
)