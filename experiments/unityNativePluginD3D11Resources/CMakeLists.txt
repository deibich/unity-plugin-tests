add_library(unityNativePluginD3D11Resources SHARED
"UnityNativePluginD3D11Resources.cpp"
)

target_link_libraries(unityNativePluginD3D11Resources 
PRIVATE
    unityInterfaces
    d3d11.lib
    
)

if(${INSTALL_EXPERIMENTS})
    install(TARGETS unityNativePluginD3D11Resources DESTINATION ${UNITY_PROJECT_ROOT_DIR}/Assets/${UNITY_ASSETS_SUBDIRECTORY_EXPERIMENTS}/UnityNativePluginD3D11Resources)
endif()