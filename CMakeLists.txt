cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Perfect_Jazz)

#### Setup Directories ####
#Main output directory
set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
# SFML - graphics library
add_subdirectory("lib/sfml" EXCLUDE_FROM_ALL)
#include_directories("lib/sfml/include")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

# B2D - Box2D phyics library
add_subdirectory("lib/b2d/Box2D" EXCLUDE_FROM_ALL)
#include_directories("lib/b2d/Box2D/")
set(B2D_INCS "lib/b2d/Box2D/")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Add Engine and our own library projects####
file(GLOB_RECURSE RESOURCE_FILES "res/*.*")
####
file(GLOB_RECURSE SOURCE_FILES engine/*.cpp engine/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/engine/" PUBLIC SYSTEM ${B2D_INCS} )
target_link_libraries(lib_engine lib_tile_level_loader lib_maths lib_ecm Box2D sfml-graphics sfml-audio)

## Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/" INTERFACE ${SFML_INCS})

## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

## ECM lib
file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm" )
target_link_libraries(lib_ecm PRIVATE lib_maths)

#### Adding Res folder ####
file(COPY res DESTINATION ${CMAKE_BINARY_DIR})

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)
	
	
#### Perfect Jazz Files ####
file(GLOB_RECURSE SOURCES PerfectJazz/*.cpp PerfectJazz/*.h)
file(GLOB_RECURSE CMPNTS PerfectJazz/components/*.cpp PerfectJazz/components/*.h)
file(GLOB_RECURSE SCENES PerfectJazz/scenes/*.cpp PerfectJazz/scenes/*.h)
file(GLOB_RECURSE ENEMIES PerfectJazz/enemies/*.cpp PerfectJazz/enemies/*.h)
file(GLOB_RECURSE PLAYER PerfectJazz/player/*.cpp PerfectJazz/player/*.h)
file(GLOB_RECURSE SETTINGS PerfectJazz/settings/*.cpp PerfectJazz/settings/*.h)
file(GLOB_RECURSE PANELS PerfectJazz/panels/*.cpp PerfectJazz/panels/*.h)
file(GLOB_RECURSE BACKGROUND PerfectJazz/background/*.cpp PerfectJazz/background/*.h)
add_executable(PerfectJazz ${SOURCES} ${RESOURCE_FILES})
source_group("components" FILES ${CMPNTS})
source_group("resources" FILES ${RESOURCE_FILES})
source_group("enemies" FILES ${ENEMIES})
source_group("player" FILES ${PLAYER})

#target_include_directories(PerfectJazz SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
target_link_libraries(PerfectJazz lib_engine)
set(EXECUTABLES ${EXECUTABLES} PerfectJazz)
source_group("settings" FILES ${SETTINGS})
source_group("panels" FILES ${PANELS})
source_group("background" FILES ${BACKGROUND})
#target_include_directories(PerfectJazz SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
target_link_libraries(PerfectJazz lib_engine)
set(EXECUTABLES ${EXECUTABLES} PerfectJazz)
add_dependencies(PerfectJazz copy_resources)

set_target_properties(PerfectJazz 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
