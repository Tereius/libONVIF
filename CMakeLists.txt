cmake_minimum_required(VERSION 3.21.1)
project(QtAppBase)
include(QtAppBase)

qt_app_project_setup(PROJECT_SETUP_INFO)
project(${PROJECT_SETUP_INFO})

qt_app_setup()
include_directories("${PROJECT_BINARY_DIR}")

# Handle precompiled header stuff
#set(USE_PRECOMPILED_HEADERS false CACHE BOOL "Use precompiled headers?")
#if(USE_PRECOMPILED_HEADERS)
#	include(cotire)
#	if(MSVC)
#		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
#	endif()
#endif()

add_subdirectory(src)

add_subdirectory(doc doxygen EXCLUDE_FROM_ALL)
