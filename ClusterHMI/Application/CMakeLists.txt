cmake_minimum_required(VERSION 3.5.1)
project(ClusterHMI)

if(NOT TARGET Kanzi::kzappfw)
    find_package(Kanzi REQUIRED CONFIG CMAKE_FIND_ROOT_PATH_BOTH)
endif()

include(kanzi-common)

add_executable(ClusterHMI src/clusterhmi.cpp)

if(ANDROID)
    target_link_libraries(ClusterHMI -Wl,--whole-archive Kanzi::kzappfw -Wl,--no-whole-archive)
else()
    target_link_libraries(ClusterHMI Kanzi::kzappfw)
endif()

target_link_libraries(ClusterHMI Kanzi::kzui Kanzi::kzcoreui Kanzi::kzjs)

set_target_properties(ClusterHMI PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
