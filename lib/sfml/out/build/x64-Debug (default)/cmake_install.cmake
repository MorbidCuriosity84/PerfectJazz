# Install script for directory: I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE DIRECTORY FILES "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/include" FILES_MATCHING REGEX "/[^/]*\\.hpp$" REGEX "/[^/]*\\.inl$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE DIRECTORY FILES "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/out/build/x64-Debug (default)/lib" FILES_MATCHING REGEX "/[^/]*\\.pdb$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/SFML" TYPE FILE FILES "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/license.md")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/SFML" TYPE FILE FILES "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/readme.md")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE DIRECTORY FILES "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/extlibs/bin/x64/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE DIRECTORY FILES "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/extlibs/libs-msvc-universal/x64/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SFML/SFMLSharedTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SFML/SFMLSharedTargets.cmake"
         "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/out/build/x64-Debug (default)/CMakeFiles/Export/lib/cmake/SFML/SFMLSharedTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SFML/SFMLSharedTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SFML/SFMLSharedTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SFML" TYPE FILE FILES "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/out/build/x64-Debug (default)/CMakeFiles/Export/lib/cmake/SFML/SFMLSharedTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SFML" TYPE FILE FILES "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/out/build/x64-Debug (default)/CMakeFiles/Export/lib/cmake/SFML/SFMLSharedTargets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SFML" TYPE FILE FILES
    "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/out/build/x64-Debug (default)/SFMLConfig.cmake"
    "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/out/build/x64-Debug (default)/SFMLConfigDependencies.cmake"
    "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/out/build/x64-Debug (default)/SFMLConfigVersion.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/out/build/x64-Debug (default)/src/SFML/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "I:/Carlos - Desktop/OneDrive - Edinburgh Napier University/- University -/Trimester 2/- Gaming Engineering/CW/Perfect Jazz/lib/sfml/out/build/x64-Debug (default)/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
