cmake_minimum_required(VERSION 2.8.12)
# Set a default search path for CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake;${CMAKE_MODULE_PATH}")
include(JSONParser)

# Parse the info.json and write a info.h file
file(READ info.json jsonInfo)
sbeParseJson(info jsonInfo)

project(${info.projectName})

# Configure a header file to pass some of the CMake settings to the source code.
include_directories("${CMAKE_CURRENT_BINARY_DIR}/src")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/src/info.h" "")
foreach(var ${info})
	string(TOUPPER "${var}" UPPER_VAR)
	string(REPLACE "." "_" UPPER_VAR "${UPPER_VAR}")
	if(${${var}} MATCHES "^[0-9]+$")
		file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/src/info.h" "#define ${UPPER_VAR} ${${var}}\n")
	else()
		file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/src/info.h" "#define ${UPPER_VAR} \"${${var}}\"\n")
	endif()
endforeach()

# Check if we use conan
if(EXISTS "${PROJECT_BINARY_DIR}/conanbuildinfo.cmake")
	include("${PROJECT_BINARY_DIR}/conanbuildinfo.cmake")
	set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
	set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
	set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
	conan_basic_setup()
elseif(EXISTS "${PROJECT_SOURCE_DIR}/conanbuildinfo.cmake")
	include("${PROJECT_SOURCE_DIR}/conanbuildinfo.cmake")
	set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
	set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
	set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
	conan_basic_setup()
endif()

# If build type is empty and there is no multi-configuration generator (like Visual Studio) choose release build.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "Default Targets")

# Handle RPATH stuff
if(UNIX)
	set(RPATH_ORIGIN false CACHE BOOL "Set the RPATH to $ORIGIN? Helpful for bundles")

	# Use, i.e. don't skip the full RPATH for the build tree
	set(CMAKE_SKIP_BUILD_RPATH OFF)
	# When building, don't use the install RPATH already
	# (but later on when installing)
	set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)
	if(RPATH_ORIGIN)
		set(CMAKE_INSTALL_RPATH "$ORIGIN/")
	else()
		set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
	endif()
	# Add the automatically determined parts of the RPATH
	# which point to directories outside the build tree to the install RPATH
	set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)
	# The RPATH to be used when installing, but only if it's not a system directory
	if(NOT RPATH_ORIGIN)
		list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
		if("${isSystemDir}" STREQUAL "-1")
			set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
		endif()
	endif()
endif()

add_subdirectory(doc doxygen EXCLUDE_FROM_ALL)

# Handle precompiled header stuff
set(USE_PRECOMPILED_HEADERS false CACHE BOOL "Use precompiled headers?")
if(USE_PRECOMPILED_HEADERS)
	include(cotire)
	if(MSVC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
	endif()
endif()

add_subdirectory(src)

# Handle CPack stuff
if(WIN32)
	set(CPACK_GENERATOR ZIP)
elseif(UNIX AND NOT APPLE)
	set(CPACK_GENERATOR TGZ)
elseif(APPLE)
	set(CPACK_GENERATOR STGZ;TGZ)
elseif(ANDROID)
	set(CPACK_GENERATOR STGZ;TGZ)
else()
endif()
set(CPACK_PACKAGE_NAME "${info.projectName}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${info.projectDescription}")
set(CPACK_PACKAGE_VENDOR "${info.vendor}")
set(CPACK_PACKAGE_CONTACT "${info.contact}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR ${info.version.major})
set(CPACK_PACKAGE_VERSION_MINOR ${info.version.minor})
set(CPACK_PACKAGE_VERSION_PATCH ${info.version.patch})
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME}{CTL_MAJOR_VERSION}.${CTL_MINOR_VERSION})
set(CPACK_PACKAGE_FILE_NAME ${PROJECT_NAME})
include(CPack)
