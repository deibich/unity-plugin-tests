cmake_minimum_required(VERSION 3.25)

project(unity-plugin-tests
    VERSION 1.0
    LANGUAGES
        CXX
)
find_package(SDL2 CONFIG REQUIRED)
add_subdirectory(unityInterfaces)
add_subdirectory(unityPluginRuntime)
add_subdirectory(experiments)

