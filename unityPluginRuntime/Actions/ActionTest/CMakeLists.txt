add_library(ActionTest SHARED
	"src/ActionTest.cpp"
)

target_link_libraries(ActionTest
	PUBLIC
		unityInterfaces
		NativeActionRuntime
		Action
)
set_target_properties(ActionTest PROPERTIES CXX_STANDARD 20)

install(TARGETS ActionTest DESTINATION ${UNITY_PROJECT_ROOT_DIR}/Assets/${UNITY_ASSETS_SUBDIRECTORY_ACTIONS}/ActionTest)
