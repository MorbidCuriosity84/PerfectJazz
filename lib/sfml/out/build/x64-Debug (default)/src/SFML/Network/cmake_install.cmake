# Install script for directory: I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/src/SFML/Network

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/out/install/x64-Debug (default)")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/out/build/x64-Debug (default)/lib/sfml-network-d.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xbinx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/out/build/x64-Debug (default)/lib/sfml-network-d-2.dll")
endif()

