cmake_minimum_required(VERSION 3.5.1)
project(DataLayerPlugin_plugin)

if(MSVC)
    option(BUILD_SHARED_LIBS "Selects whether to build and link to shared or static libraries" ON)
endif()

if(NOT KANZI_ENGINE_BUILD)
    find_package(Kanzi REQUIRED CONFIG CMAKE_FIND_ROOT_PATH_BOTH
        HINTS "$ENV{KANZI_HOME}/Engine/lib/cmake")
endif()

include(kanzi-common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Model)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/SharedMemory)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Simulate)

file(GLOB_RECURSE common_FILES  "${CMAKE_CURRENT_SOURCE_DIR}/src/Common/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/Common/*.cpp")
file(GLOB_RECURSE model_FILES  "${CMAKE_CURRENT_SOURCE_DIR}/src/Model/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/Model/*.cpp")
file(GLOB_RECURSE sharedmemory_FILES  "${CMAKE_CURRENT_SOURCE_DIR}/src/SharedMemory/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/SharedMemory/*.cpp")
file(GLOB_RECURSE simulate_FILES  "${CMAKE_CURRENT_SOURCE_DIR}/src/Simulate/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/Simulate/*.cpp")
source_group("Common" FILES ${common_FILES})
source_group("Model" FILES ${model_FILES}) 
source_group("SharedMemory" FILES ${sharedmemory_FILES}) 
source_group("Simulate" FILES ${simulate_FILES}) 

set(sources
    src/datalayerplugin.cpp
    src/datalayerplugin.hpp
    src/datalayerplugin.rc
    src/datalayerplugin_module.cpp
    src/datalayerplugin_module.hpp)

add_library(DataLayerPlugin 
			${sources}
			${common_FILES}
			${model_FILES}
			${sharedmemory_FILES}
			${simulate_FILES})

target_link_libraries(DataLayerPlugin PUBLIC Kanzi::kzcore Kanzi::kzcoreui Kanzi::kzui)

target_include_directories(DataLayerPlugin PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)

if(BUILD_SHARED_LIBS AND MSVC)
    target_compile_definitions(DataLayerPlugin PRIVATE "DATALAYERPLUGIN_API=__declspec(dllexport)")
    target_compile_definitions(DataLayerPlugin PRIVATE "DATALAYERPLUGIN_API_EXPORT")
    target_compile_definitions(DataLayerPlugin INTERFACE "DATALAYERPLUGIN_API=__declspec(dllimport)")
else()
    target_compile_definitions(DataLayerPlugin PUBLIC "DATALAYERPLUGIN_API=")
endif()

# Copy plugin dll for the Kanzi-studio project.
if(BUILD_SHARED_LIBS AND MSVC)
    set(KANZI_PROJECT_PLUGIN_PATH "${PROJECT_SOURCE_DIR}/../../lib/${PLATFORM_TARGET}/${MSVC_TAG}_$<CONFIG>_DLL")
    add_custom_command(TARGET DataLayerPlugin POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${KANZI_PROJECT_PLUGIN_PATH}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:DataLayerPlugin>" "${KANZI_PROJECT_PLUGIN_PATH}")
endif()

install_target_to_output_directory(DataLayerPlugin)
