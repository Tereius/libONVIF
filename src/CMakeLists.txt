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
)

add_library(OnvifCommon ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(OnvifCommon EXPORT_FILE_NAME OnvifCommonExport.h)
target_link_libraries(OnvifCommon "${OpenSSLLib_ssl_PATH}" "${OpenSSLLib_cryptro_PATH}" Qt5::Core)
set_target_properties(OnvifCommon PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifCommonExport.h")

# -------------------------------ONVIF Analytics-------------------------------
set(src_files 
	generated/soapAnalyticsDeviceBindingProxy.cpp
	#generated/soapAnalyticsDeviceBindingService.cpp
	OnvifAnalyticsClient.cpp
)

# private header
set(private_header_files
	generated/soapAnalyticsDeviceBindingProxy.h
	#generated/soapAnalyticsDeviceBindingService.h
)

# public header
set(public_header_files
	OnvifAnalyticsClient.h
)

add_library(OnvifAnalytics ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(OnvifAnalytics EXPORT_FILE_NAME OnvifAnalyticsExport.h)
target_link_libraries(OnvifAnalytics OnvifCommon)
set_target_properties(OnvifAnalytics PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifAnalyticsExport.h")

# -------------------------------ONVIF Device-------------------------------
set(src_files 
	generated/soapDeviceBindingProxy.cpp
	#generated/soapDeviceBindingService.cpp
	OnvifDeviceClient.cpp
)

# private header
set(private_header_files
	generated/soapDeviceBindingProxy.h
	#generated/soapDeviceBindingService.h
)

# public header
set(public_header_files
	OnvifDeviceClient.h
)

add_library(OnvifDevice ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(OnvifDevice EXPORT_FILE_NAME OnvifDeviceExport.h)
target_link_libraries(OnvifDevice OnvifCommon)
set_target_properties(OnvifDevice PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifDeviceExport.h")

# -------------------------------ONVIF Display-------------------------------
set(src_files 
	generated/soapDisplayBindingProxy.cpp
	#generated/soapDisplayBindingService.cpp
	OnvifDisplayClient.cpp
)

# private header
set(private_header_files
	generated/soapDisplayBindingProxy.h
	#generated/soapDisplayBindingService.h
)

# public header
set(public_header_files
	OnvifDisplayClient.h
)

add_library(OnvifDisplay ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(OnvifDisplay EXPORT_FILE_NAME OnvifDisplayExport.h)
target_link_libraries(OnvifDisplay OnvifCommon)
set_target_properties(OnvifDisplay PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifDisplayExport.h")

# -------------------------------ONVIF Imaging-------------------------------
set(src_files 
	generated/soapImagingBindingProxy.cpp
	#generated/soapImagingBindingService.cpp
	OnvifImagingClient.cpp
)

# private header
set(private_header_files
	generated/soapImagingBindingProxy.h
	#generated/soapImagingBindingService.h
)

# public header
set(public_header_files
	OnvifImagingClient.h
)

add_library(OnvifImaging ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(OnvifImaging EXPORT_FILE_NAME OnvifImagingExport.h)
target_link_libraries(OnvifImaging OnvifCommon)
#set_target_properties(OnvifImaging PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifImagingExport.h")

# -------------------------------ONVIF Media-------------------------------
set(src_files 
	generated/soapMediaBindingProxy.cpp
	#generated/soapMediaBindingService.cpp
	OnvifMediaClient.cpp
)

# private header
set(private_header_files
	generated/soapMediaBindingProxy.h
	#generated/soapMediaBindingService.h
)

# public header
set(public_header_files
		OnvifMediaClient.h
)

add_library(OnvifMedia ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(OnvifMedia EXPORT_FILE_NAME OnvifMediaExport.h)
target_link_libraries(OnvifMedia OnvifCommon)
#set_target_properties(OnvifMedia PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifMediaExport.h")

# -------------------------------ONVIF PTZ-------------------------------
set(src_files 
	generated/soapPTZBindingProxy.cpp
	#generated/soapPTZBindingService.cpp
	OnvifPtzClient.cpp
)

# private header
set(private_header_files
	generated/soapPTZBindingProxy.h
	#generated/soapPTZBindingService.h
)

# public header
set(public_header_files
	OnvifPtzClient.h
)

add_library(OnvifPtz ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(OnvifPtz EXPORT_FILE_NAME OnvifPtzExport.h)
target_link_libraries(OnvifPtz OnvifCommon)
#set_target_properties(OnvifPtz PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifPtzExport.h")

# -------------------------------ONVIF Event-------------------------------
set(src_files 
	generated/soapPullPointSubscriptionBindingProxy.cpp
	#generated/soapPullPointSubscriptionBindingService.cpp
	OnvifEventClient.cpp
	OnvifPullPoint.cpp
)

# private header
set(private_header_files
	generated/soapPullPointSubscriptionBindingProxy.h
	#generated/soapPullPointSubscriptionBindingService.h
)

# public header
set(public_header_files
	OnvifEventClient.h
	OnvifPullPoint.h
)

add_library(OnvifEvent ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(OnvifEvent EXPORT_FILE_NAME OnvifEventExport.h)
target_link_libraries(OnvifEvent OnvifCommon)
set_target_properties(OnvifEvent PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifEventExport.h")

# -------------------------------ONVIF Receiver-------------------------------
set(src_files 
	generated/soapReceiverBindingProxy.cpp
	#generated/soapReceiverBindingService.cpp
	OnvifReceiverClient.cpp
)

# private header
set(private_header_files
	generated/soapReceiverBindingProxy.h
	#generated/soapReceiverBindingService.h
)

# public header
set(public_header_files
	OnvifReceiverClient.h
)

add_library(OnvifReceiver ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(OnvifReceiver EXPORT_FILE_NAME OnvifReceiverExport.h)
target_link_libraries(OnvifReceiver OnvifCommon)
#set_target_properties(OnvifReceiver PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifReceiverExport.h")

# -------------------------------ONVIF Recording-------------------------------
set(src_files 
	generated/soapRecordingBindingProxy.cpp
	#generated/soapRecordingBindingService.cpp
	OnvifRecordingClient.cpp
)

# private header
set(private_header_files
	generated/soapRecordingBindingProxy.h
	#generated/soapRecordingBindingService.h
)

# public header
set(public_header_files
	OnvifRecordingClient.h
)

add_library(OnvifRecording ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(OnvifRecording EXPORT_FILE_NAME OnvifRecordingExport.h)
target_link_libraries(OnvifRecording OnvifCommon)
#set_target_properties(OnvifRecording PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifRecordingExport.h")

# -------------------------------ONVIF Discovery-------------------------------
set(src_files 
	generated/soapRemoteDiscoveryBindingProxy.cpp
	#generated/soapRemoteDiscoveryBindingService.cpp
	#gsoap/wsddapi.c
	OnvifDiscoveryClient.cpp
)

set_source_files_properties(${src_files} PROPERTIES LANGUAGE CXX)

# private header
set(private_header_files
	generated/soapRemoteDiscoveryBindingProxy.h
	#generated/soapRemoteDiscoveryBindingService.h
	#gsoap/wsddapi.h
)

# public header
set(public_header_files
	OnvifDiscoveryClient.h
)

add_library(OnvifDiscovery ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(OnvifDiscovery EXPORT_FILE_NAME OnvifDiscoveryExport.h)
target_link_libraries(OnvifDiscovery OnvifCommon)
set_target_properties(OnvifDiscovery PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifDiscoveryExport.h")

# -------------------------------ONVIF Replay-------------------------------
set(src_files 
	generated/soapReplayBindingProxy.cpp
	#generated/soapReplayBindingService.cpp
	OnvifReplayClient.cpp
)

# private header
set(private_header_files
	generated/soapReplayBindingProxy.h
	#generated/soapReplayBindingService.h
)

# public header
set(public_header_files
	OnvifReplayClient.h
)

add_library(OnvifReplay ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(OnvifReplay EXPORT_FILE_NAME OnvifReplayExport.h)
target_link_libraries(OnvifReplay OnvifCommon)
#set_target_properties(OnvifReplay PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifReplayExport.h")

# -------------------------------------------------------------------------

# Testsuite
set(src_files
	main.cpp
)

# private header
set(private_header_files

)

add_executable(Testsuite ${src_files} ${private_header_files})
target_link_libraries(Testsuite OnvifDevice OnvifEvent)

if(MSVC)
	set_target_properties(Testsuite OnvifCommon OnvifDevice OnvifDiscovery OnvifReplay OnvifRecording OnvifReceiver OnvifPtz OnvifMedia OnvifImaging OnvifEvent OnvifDisplay OnvifAnalytics PROPERTIES COMPILE_FLAGS "/bigobj")
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
	Testsuite
	OnvifCommon
	OnvifDevice
	OnvifDiscovery
	OnvifReplay
	OnvifRecording
	OnvifReceiver
	OnvifPtz
	OnvifMedia
	OnvifImaging
	OnvifEvent
	OnvifDisplay
	OnvifAnalytics
	EXPORT libONVIFTargets RUNTIME DESTINATION bin ARCHIVE DESTINATION lib PUBLIC_HEADER DESTINATION include
)
install(EXPORT libONVIFTargets DESTINATION cmake)

install(FILES "${CMAKE_BINARY_DIR}/libONVIFConfig.cmake" "${CMAKE_BINARY_DIR}/libONVIFVersion.cmake" DESTINATION cmake)
