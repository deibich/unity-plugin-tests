# SHARED ist required because unity allows natives plugins as shared only
add_library(unityNativePluginSequence SHARED
    "src/UnityNativePluginSequence.cpp"
)

target_link_libraries(unityNativePluginSequence
    PRIVATE
        unityInterfaces
)

if(${INSTALL_EXPERIMENTS})
    install(TARGETS unityNativePluginSequence DESTINATION ${UNITY_PROJECT_ROOT_DIR}/Assets/${UNITY_ASSETS_SUBDIRECTORY_EXPERIMENTS}/UnityNativePluginSequence)
endif()