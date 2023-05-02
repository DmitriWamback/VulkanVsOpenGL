cmake_minimum_required(VERSION 3.14)
project(VKGLMTL-app C CXX)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/glfw)
add_subdirectory(sub/glm)
find_package(GLEW REQUIRED)
find_package(Vulkan REQUIRED)
add_definitions(-DGL_SILENCE_DEPRECATION)

list(APPEND SOURCES
    main.cpp
)

list(APPEND ADDITIONS
    "--std=c++17"
)
if(APPLE)
    list(APPEND ADDITIONS
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
    )
endif()
add_executable(VKGLMTL-app ${SOURCES})
target_compile_features(VKGLMTL-app PRIVATE cxx_std_17)
target_link_libraries(VKGLMTL-app glfw glm GLEW::GLEW Vulkan::Vulkan ${ADDITIONS})