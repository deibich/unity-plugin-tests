add_library(GfxPluginTest SHARED
	"GfxPluginTest.cpp"
)

target_link_libraries(GfxPluginTest
	PRIVATE
		unityInterfaces
)

if(${INSTALL_EXPERIMENTS})
	install(TARGETS GfxPluginTest DESTINATION ${UNITY_PROJECT_ROOT_DIR}/Assets/${UNITY_ASSETS_SUBDIRECTORY_EXPERIMENTS}/GfxPluginTest)
endif()
