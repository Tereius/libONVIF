include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
find_package(CommonLibs_DIR NAMES CommonLibs)
find_package(Qt5Core)
find_library(OpenSSLLib_cryptro_PATH NAMES libeay libeay32 libcrypto libcrypto32 PATH_SUFFIXES "lib")
find_library(OpenSSLLib_ssl_PATH NAMES ssleay ssleay32 libssl libssl32 PATH_SUFFIXES "lib")
find_path(OpenSSLLib_include_DIR NAMES openssl/ssl.h PATH_SUFFIXES "include")

set(CMAKE_AUTOMOC ON)
set(BUILD_SHARED_LIBS true CACHE BOOL "Build shared or static lib?")
set(CMAKE_DEBUG_POSTFIX d) # Append "d" if debug lib.

include_directories("${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" "${OpenSSLLib_include_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/generated" "${CMAKE_CURRENT_SOURCE_DIR}/gsoap")

add_definitions(-DWITH_OPENSSL)
if(MSVC)
	add_definitions(-DNOMINMAX)
endif()
if(WIN32 AND BUILD_SHARED_LIBS)
	add_definitions(-DSOAP_STD_EXPORTS)
endif()

# -------------------------------ONVIF Common-------------------------------
set(src_files 
	generated/soapC.cpp
	gsoap/duration.cpp
	gsoap/qdatetime.cpp
	gsoap/AbsoluteOrRelativeTimeType.cpp
	gsoap/qstring.cpp
	gsoap/stdsoap2.cpp
	gsoap/dom.cpp
	gsoap/httpda.c
	gsoap/smdevp.c
	gsoap/wsaapi.c
	gsoap/wsseapi-lite.c
	SoapCtx.cpp
	Client.cpp
	Response.cpp
	JsonHelper.cpp
	SoapHelper.cpp
)

set_source_files_properties(${src_files} PROPERTIES LANGUAGE CXX)

# private header
set(private_header_files
	gsoap/stlvector.h
)

# public header
set(public_header_files
	generated/soapStub.h
	generated/soapH.h
	gsoap/stdsoap2.h
	gsoap/httpda.h
	gsoap/smdevp.h
	gsoap/wsaapi.h
	gsoap/wsseapi-lite.h
	gsoap/threads.h
	gsoap/AbsoluteOrRelativeTime.h
	SoapCtx.h
	Request.h
	Response.h
	Client.h
	SafeBool.h
	global.h
	JsonHelper.h
	SoapHelper.h
)

add_library(onvifcommon ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifcommon EXPORT_FILE_NAME onvifcommonExport.h)
target_link_libraries(onvifcommon "${OpenSSLLib_ssl_PATH}" "${OpenSSLLib_cryptro_PATH}" Qt5::Core)
set_target_properties(onvifcommon PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/onvifcommonExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifcommon)
endif()

# -------------------------------ONVIF Analytics-------------------------------
set(src_files 
	generated/soapAnalyticsDeviceBindingProxy.cpp
	#generated/soapAnalyticsDeviceBindingService.cpp
	onvifanalyticsClient.cpp
)

# private header
set(private_header_files
	generated/soapAnalyticsDeviceBindingProxy.h
	#generated/soapAnalyticsDeviceBindingService.h
)

# public header
set(public_header_files
	onvifanalyticsClient.h
)

add_library(onvifanalytics ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifanalytics EXPORT_FILE_NAME onvifanalyticsExport.h)
target_link_libraries(onvifanalytics onvifcommon)
set_target_properties(onvifanalytics PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/onvifanalyticsExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifanalytics)
endif()

# -------------------------------ONVIF Device-------------------------------
set(src_files 
	generated/soapDeviceBindingProxy.cpp
	#generated/soapDeviceBindingService.cpp
	onvifdeviceClient.cpp
)

# private header
set(private_header_files
	generated/soapDeviceBindingProxy.h
	#generated/soapDeviceBindingService.h
)

# public header
set(public_header_files
	onvifdeviceClient.h
)

add_library(onvifdevice ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifdevice EXPORT_FILE_NAME onvifdeviceExport.h)
target_link_libraries(onvifdevice onvifcommon)
set_target_properties(onvifdevice PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/onvifdeviceExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifdevice)
endif()

# -------------------------------ONVIF Display-------------------------------
set(src_files 
	generated/soapDisplayBindingProxy.cpp
	#generated/soapDisplayBindingService.cpp
	onvifdisplayClient.cpp
)

# private header
set(private_header_files
	generated/soapDisplayBindingProxy.h
	#generated/soapDisplayBindingService.h
)

# public header
set(public_header_files
	onvifdisplayClient.h
)

add_library(onvifdisplay ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifdisplay EXPORT_FILE_NAME onvifdisplayExport.h)
target_link_libraries(onvifdisplay onvifcommon)
set_target_properties(onvifdisplay PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/onvifdisplayExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifdisplay)
endif()

# -------------------------------ONVIF Imaging-------------------------------
set(src_files 
	generated/soapImagingBindingProxy.cpp
	#generated/soapImagingBindingService.cpp
	onvifimagingClient.cpp
)

# private header
set(private_header_files
	generated/soapImagingBindingProxy.h
	#generated/soapImagingBindingService.h
)

# public header
set(public_header_files
	onvifimagingClient.h
)

add_library(onvifimaging ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifimaging EXPORT_FILE_NAME onvifimagingExport.h)
target_link_libraries(onvifimaging onvifcommon)
#set_target_properties(onvifimaging PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/onvifimagingExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifimaging)
endif()

# -------------------------------ONVIF Media-------------------------------
set(src_files 
	generated/soapMediaBindingProxy.cpp
	#generated/soapMediaBindingService.cpp
	onvifmediaClient.cpp
)

# private header
set(private_header_files
	generated/soapMediaBindingProxy.h
	#generated/soapMediaBindingService.h
)

# public header
set(public_header_files
		onvifmediaClient.h
)

add_library(onvifmedia ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifmedia EXPORT_FILE_NAME onvifmediaExport.h)
target_link_libraries(onvifmedia onvifcommon)
#set_target_properties(onvifmedia PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/onvifmediaExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifmedia)
endif()

# -------------------------------ONVIF PTZ-------------------------------
set(src_files 
	generated/soapPTZBindingProxy.cpp
	#generated/soapPTZBindingService.cpp
	onvifptzClient.cpp
)

# private header
set(private_header_files
	generated/soapPTZBindingProxy.h
	#generated/soapPTZBindingService.h
)

# public header
set(public_header_files
	onvifptzClient.h
)

add_library(onvifptz ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifptz EXPORT_FILE_NAME onvifptzExport.h)
target_link_libraries(onvifptz onvifcommon)
#set_target_properties(onvifptz PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/onvifptzExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifptz)
endif()

# -------------------------------ONVIF Event-------------------------------
set(src_files 
	generated/soapPullPointSubscriptionBindingProxy.cpp
	#generated/soapPullPointSubscriptionBindingService.cpp
	onvifeventClient.cpp
	OnvifPullPoint.cpp
)

# private header
set(private_header_files
	generated/soapPullPointSubscriptionBindingProxy.h
	#generated/soapPullPointSubscriptionBindingService.h
)

# public header
set(public_header_files
	onvifeventClient.h
	OnvifPullPoint.h
)

add_library(onvifevent ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifevent EXPORT_FILE_NAME onvifeventExport.h)
target_link_libraries(onvifevent onvifcommon)
set_target_properties(onvifevent PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/onvifeventExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifevent)
endif()

# -------------------------------ONVIF Receiver-------------------------------
set(src_files 
	generated/soapReceiverBindingProxy.cpp
	#generated/soapReceiverBindingService.cpp
	onvifreceiverClient.cpp
)

# private header
set(private_header_files
	generated/soapReceiverBindingProxy.h
	#generated/soapReceiverBindingService.h
)

# public header
set(public_header_files
	onvifreceiverClient.h
)

add_library(onvifreceiver ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifreceiver EXPORT_FILE_NAME onvifreceiverExport.h)
target_link_libraries(onvifreceiver onvifcommon)
#set_target_properties(onvifreceiver PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/onvifreceiverExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifreceiver)
endif()

# -------------------------------ONVIF Recording-------------------------------
set(src_files 
	generated/soapRecordingBindingProxy.cpp
	#generated/soapRecordingBindingService.cpp
	onvifrecordingClient.cpp
)

# private header
set(private_header_files
	generated/soapRecordingBindingProxy.h
	#generated/soapRecordingBindingService.h
)

# public header
set(public_header_files
	onvifrecordingClient.h
)

add_library(onvifrecording ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifrecording EXPORT_FILE_NAME onvifrecordingExport.h)
target_link_libraries(onvifrecording onvifcommon)
#set_target_properties(onvifrecording PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/onvifrecordingExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifrecording)
endif()

# -------------------------------ONVIF Discovery-------------------------------
set(src_files
	# generated/soapRemoteDiscoveryBindingProxy.cpp
	# generated/soapRemoteDiscoveryBindingService.cpp
	# gsoap/wsddapi.c
	OnvifdiscoveryClient.cpp
	# OnvifDiscover.cpp
	OnvifDiscovery.cpp
	generated/soapwsddProxy.cpp
)

set_source_files_properties(${src_files} PROPERTIES LANGUAGE CXX)

# private header
set(private_header_files
	# generated/soapRemoteDiscoveryBindingProxy.h
	# generated/soapRemoteDiscoveryBindingService.h
)

# public header
set(public_header_files
	OnvifdiscoveryClient.h
	DeleterDuplicator.h
	# OnvifDiscover.h
	generated/soapwsddProxy.h
	OnvifDiscovery.h
)

add_library(onvifdiscovery ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifdiscovery EXPORT_FILE_NAME onvifdiscoveryExport.h)
target_link_libraries(onvifdiscovery onvifcommon)
set_target_properties(onvifdiscovery PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/onvifdiscoveryExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifdiscovery)
endif()

# -------------------------------ONVIF Replay-------------------------------
set(src_files 
	generated/soapReplayBindingProxy.cpp
	#generated/soapReplayBindingService.cpp
	onvifreplayClient.cpp
)

# private header
set(private_header_files
	generated/soapReplayBindingProxy.h
	#generated/soapReplayBindingService.h
)

# public header
set(public_header_files
	onvifreplayClient.h
)

add_library(onvifreplay ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifreplay EXPORT_FILE_NAME onvifreplayExport.h)
target_link_libraries(onvifreplay onvifcommon)
#set_target_properties(onvifreplay PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/onvifreplayExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifreplay)
endif()

# -------------------------------------------------------------------------

# info tool
set(src_files
	main.cpp
	CmdLineParser.cpp
	OnvifDevice.cpp
)

# private header
set(private_header_files
	CmdLineParser.h
	OnvifDevice.h
)

add_executable(onvifinfo ${src_files} ${private_header_files})
target_link_libraries(onvifinfo onvifcommon onvifdevice onvifdiscovery onvifreplay onvifrecording onvifreceiver onvifptz onvifmedia onvifimaging onvifevent onvifdisplay onvifanalytics)
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifinfo)
endif()

if(MSVC)
	set_target_properties(onvifinfo onvifcommon onvifdevice onvifdiscovery onvifreplay onvifrecording onvifreceiver onvifptz onvifmedia onvifimaging onvifevent onvifdisplay onvifanalytics PROPERTIES COMPILE_FLAGS "/bigobj")
endif()

set(install_root "${CMAKE_INSTALL_PREFIX}")
set(install_include_dir "${install_root}/include")
set(install_runtime_dir "${install_root}/bin")
set(install_lib_dir "${install_root}/lib")
set(install_cmake_dir "${install_root}/lib/cmake")

set(INCLUDE_INSTALL_DIR "include")
set(CMAKE_INSTALL_DIR "cmake")
set(BIN_INSTALL_DIR "bin")
set(LIB_INSTALL_DIR "lib")
configure_package_config_file("${CMAKE_SOURCE_DIR}/libONVIFConfig.cmake.in" "${CMAKE_BINARY_DIR}/libONVIFConfig.cmake" INSTALL_DESTINATION cmake
                              PATH_VARS INCLUDE_INSTALL_DIR CMAKE_INSTALL_DIR BIN_INSTALL_DIR LIB_INSTALL_DIR)

write_basic_package_version_file("${CMAKE_BINARY_DIR}/libONVIFVersion.cmake" VERSION 1.0.0 COMPATIBILITY SameMajorVersion) # Project version is uses
							  
# add the install target
install(TARGETS 
	onvifinfo
	onvifcommon
	onvifdevice
	onvifdiscovery
	onvifreplay
	onvifrecording
	onvifreceiver
	onvifptz
	onvifmedia
	onvifimaging
	onvifevent
	onvifdisplay
	onvifanalytics
	EXPORT libONVIFTargets RUNTIME DESTINATION bin ARCHIVE DESTINATION lib PUBLIC_HEADER DESTINATION include
)
install(EXPORT libONVIFTargets DESTINATION cmake)

install(FILES "${CMAKE_BINARY_DIR}/libONVIFConfig.cmake" "${CMAKE_BINARY_DIR}/libONVIFVersion.cmake" DESTINATION cmake)
