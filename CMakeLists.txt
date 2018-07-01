cmake_minimum_required(VERSION 2.8.12)

#------------global variables------------
project(libONVIF)
# The version number.
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
set(PROJECT_VENDOR "Björn Stresing")
set(PROJECT_COPYRIGHT_YEAR "2018")
set(PROJECT_DOMAIN_FIRST "com")
set(PROJECT_DOMAIN_SECOND "github")
set(PROJECT_DOMAIN_THIRD "Tereius")
set(PROJECT_CONTACT "bjoern.stresing@gmx.de")
set(PROJECT_DOMAIN "${PROJECT_DOMAIN_FIRST}.${PROJECT_DOMAIN_SECOND}.${PROJECT_DOMAIN_THIRD}")
set(PROJECT_DESCRIPTION "A client side ONVIF library")
#----------------------------------------

# If build type is empty and there is no multi-configuration generator (like Visual Studio) choose release build.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "Default Targets")

# Handle RPATH stuff
if (UNIX)
	set(RPATH_ORIGIN false CACHE BOOL "Set the RPATH to $ORIGIN? Helpful for bundles")

	# Set a default search path for CMake modules
	set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

	# Use, i.e. don't skip the full RPATH for the build tree
	set(CMAKE_SKIP_BUILD_RPATH  OFF)
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

# Configure a header file to pass some of the CMake settings to the source code.
configure_file("${CMAKE_SOURCE_DIR}/src/info.in" "${PROJECT_BINARY_DIR}/src/info.h")
include_directories("${PROJECT_BINARY_DIR}/src")

# Handle doxygen stuff
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
	configure_file("${CMAKE_SOURCE_DIR}/src/Doxyfile.in" "${PROJECT_BINARY_DIR}/Doxyfile" @ONLY)
	add_custom_target(doc "${DOXYGEN_EXECUTABLE}" "${PROJECT_BINARY_DIR}/Doxyfile" WORKING_DIRECTORY "${PROJECT_BINARY_DIR}" COMMENT "Generating API documentation with Doxygen" VERBATIM)
	message(STATUS "Use target \"doc\" to generate doxygen")
endif(DOXYGEN_FOUND)

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
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_VENDOR "${PROJECT_VENDOR}")
set(CPACK_PACKAGE_CONTACT "${PROJECT_CONTACT}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME}{CTL_MAJOR_VERSION}.${CTL_MINOR_VERSION})
set(CPACK_PACKAGE_FILE_NAME  ${PROJECT_NAME})
include(CPack)
