add_library(unityNativePluginRenderAPI SHARED
    "src/UnityNativePluginRenderAPI.cpp"
    "src/RenderAPI/RenderAPI.cpp"
 "src/RenderAPI/RenderAPI_D3D11.cpp" "src/include/RenderAPI/RenderAPI_D3D11.h")

target_include_directories(unityNativePluginRenderAPI
    PUBLIC
        "include"
    PRIVATE
        "src/include"
)

target_link_libraries(unityNativePluginRenderAPI 
    PRIVATE
        unityInterfaces
        d3d11.lib
)

if(${INSTALL_EXPERIMENTS})
    install(TARGETS unityNativePluginRenderAPI DESTINATION ${UNITY_PROJECT_ROOT_DIR}/Assets/${UNITY_ASSETS_SUBDIRECTORY_EXPERIMENTS}/UnityNativePluginRenderAPI)
endif()
