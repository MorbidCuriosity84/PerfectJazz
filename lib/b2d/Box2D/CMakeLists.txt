#-- Box2D CMake script.
#-- https://cmake.org/

cmake_minimum_required(VERSION 3.9)
# Compiler flags
if (MSVC)
    #Compile with all cores and with Exception handling
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc" CACHE INTERNAL "" FORCE)
endif(MSVC)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Box2D CXX)

file(GLOB_RECURSE B2D_FILES  Box2D/**.cpp Box2D/**.h)
add_library(Box2D STATIC ${B2D_FILES})

include_directories(${PROJECT_SOURCE_DIR})
set_target_properties(Box2D PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Build/bin/")


SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Build/bin/")

option(B2D_Build_HelloWorld "Builds small test executable" OFF)

IF(${B2D_Build_HelloWorld})
    add_executable(HelloWorld "HelloWorld/HelloWorld.cpp")
    target_link_libraries(HelloWorld Box2D)
ENDIF(${B2D_Build_HelloWorld})

option(B2D_Build_Testbed "Builds Tests" OFF)

IF(${B2D_Build_Testbed})
    MESSAGE(FATAL_ERROR "Testbed not supported with CMake yet")
#TODO
#    file(GLOB_RECURSE GLEW_FILES  glew/**.c glew/**.h )
#    add_library(GLEW STATIC ${GLEW_FILES})
#    file(GLOB_RECURSE GLFW_FILES  glfw/*.c glfw/*.h  glfw/*.m)
#    add_library(GLFW STATIC ${GLFW_FILES})
#    file(GLOB_RECURSE IMGUI  imgui/**.cpp imgui/**.h)
#    add_library(IMGUI STATIC ${IMGUI})
#
#
#    file(GLOB_RECURSE TEST_FILES Testbed/**.cpp Testbed/**.h)
#    add_executable(Testbed ${TEST_FILES})
#    target_link_libraries(Testbed Box2D GLEW GLFW IMGUI)
ENDIF(${B2D_Build_Testbed})
