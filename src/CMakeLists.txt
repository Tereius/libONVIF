include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
find_package(CommonLibs QUIET)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_library(OpenSSL_cryptro_PATH NAMES libeay libeay32 libcrypto libcrypto32 eay crypto PATH_SUFFIXES "lib")
find_library(OpenSSL_ssl_PATH NAMES ssleay ssleay32 libssl libssl32 eay ssl PATH_SUFFIXES "lib")
find_path(OpenSSL_include_DIR NAMES openssl/ssl.h PATH_SUFFIXES "include")
if(ENABLE_CODESYNTHESIS)
	find_program(Gsoap_wsdl2h_PATH NAMES wsdl2h PATH_SUFFIXES "bin")
	find_program(Gsoap_soapcpp2_PATH NAMES soapcpp2 PATH_SUFFIXES "bin")
	find_path(Gsoap_import_DIR NAMES wsdd5.h PATH_SUFFIXES "share/gsoap/import" "share/gsoap" "share")
endif()

set(CMAKE_AUTOMOC ON)
set(BUILD_SHARED_LIBS true CACHE BOOL "Build shared or static lib?")
set(ENABLE_CODESYNTHESIS false CACHE BOOL "Run wsdl2h and soapcpp2?")
set(CMAKE_DEBUG_POSTFIX d) # Append "d" if debug lib.
set(HAS_OPENSSL OFF)
if(OpenSSL_include_DIR AND OpenSSL_cryptro_PATH AND OpenSSL_ssl_PATH)
	set(HAS_OPENSSL ON)
endif()

link_directories("${_qt5Core_install_prefix}/lib")
include_directories("${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/generated" "${CMAKE_CURRENT_SOURCE_DIR}/gsoap")
if(HAS_OPENSSL)
	include_directories("${OpenSSL_include_DIR}")
	add_definitions(-DWITH_OPENSSL)
else()
	message(STATUS "SSL/TLS disabled because of missing OpenSSL library")
endif()

if(WIN32)
	add_definitions(-DOS_WIN32)
endif()

if(MSVC)
	add_definitions(-DNOMINMAX)
endif()

if(WIN32 AND BUILD_SHARED_LIBS)
	add_definitions(-DSOAP_STD_EXPORTS)
endif()


# -------------------------------GSOAP synthesis-------------------------------

set(GSOAP_DIRS "${Gsoap_import_DIR}:${Gsoap_import_DIR}/import:${CMAKE_CURRENT_SOURCE_DIR}/gsoap")
if(ENABLE_CODESYNTHESIS)
	add_custom_target(Synthesis
										COMMAND ${Gsoap_wsdl2h_PATH} -c++11 -z7 -d -p -j -t typemap.dat -o generated.h
										http://www.onvif.org/onvif/ver10/analyticsdevice.wsdl
										http://www.onvif.org/onvif/ver10/replay.wsdl
										http://www.onvif.org/onvif/ver10/search.wsdl
										http://www.onvif.org/onvif/ver10/recording.wsdl
										http://www.onvif.org/onvif/ver10/receiver.wsdl
										http://www.onvif.org/onvif/ver20/ptz/wsdl/ptz.wsdl
										http://www.onvif.org/onvif/ver10/media/wsdl/media.wsdl
										http://www.onvif.org/onvif/ver20/media/wsdl/media.wsdl
										http://www.onvif.org/onvif/ver20/imaging/wsdl/imaging.wsdl
										http://www.onvif.org/onvif/ver10/display.wsdl
										http://www.onvif.org/onvif/ver10/events/wsdl/event.wsdl
										http://www.onvif.org/onvif/ver10/device/wsdl/devicemgmt.wsdl
										http://www.onvif.org/onvif/ver20/analytics/wsdl/analytics.wsdl
										COMMAND ${Gsoap_soapcpp2_PATH} -Ed -Ec -c++11 -z4 -a -j -L -x -n -d ${CMAKE_CURRENT_SOURCE_DIR}/generated -I ${GSOAP_DIRS} generated.h
										COMMAND $<TARGET_FILE:headerParser> generated.h
										COMMAND ${CMAKE_COMMAND} -E copy GsoapResolver.h ${CMAKE_CURRENT_SOURCE_DIR}/generated
										WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/wsdl VERBATIM)

	add_dependencies(Synthesis headerParser)
endif()

# -------------------------------Header parser-------------------------------

set(src_files
		headerParser/main.cpp
		)

add_executable(headerParser ${src_files})

# -------------------------------ONVIF Common-------------------------------
set(src_files
		generated/soapC.cpp
		gsoap/duration.c
		gsoap/qdatetime.cpp
		gsoap/AbsoluteOrRelativeTimeType.cpp
		gsoap/qstring.cpp
		gsoap/stdsoap2.cpp
		gsoap/dom.cpp
		gsoap/wsaapi.c
		gsoap/qstringCompare.cpp
		SoapCtx.cpp
		SoapAuthHandler.cpp
		Client.cpp
		SoapHelper.cpp
		)

if(HAS_OPENSSL)
	set(src_files ${src_files} gsoap/smdevp.c gsoap/httpda.c gsoap/mecevp.c gsoap/wsseapi.c)
else()
	set(src_files ${src_files} gsoap/wsseapi-lite.c)
endif()

# private header
set(private_header_files
		gsoap/stlvector.h
		)

# public header
set(public_header_files
		generated/soapStub.h
		generated/soapH.h
		gsoap/stdsoap2.h
		gsoap/wsaapi.h
		gsoap/AbsoluteOrRelativeTime.h
		gsoap/qstringCompare.h
		SoapCtx.h
		SoapAuthHandler.h
		Request.h
		Response.h
		Client.h
		global.h
		SoapHelper.h
		)

if(HAS_OPENSSL)
	set(public_header_files ${public_header_files} gsoap/smdevp.h gsoap/httpda.h gsoap/threads.h gsoap/mecevp.h gsoap/wsseapi.h)
else()
	set(public_header_files ${public_header_files} gsoap/wsseapi-lite.h)
endif()

set_source_files_properties(${src_files} PROPERTIES LANGUAGE CXX)

add_library(onvifcommon ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifcommon EXPORT_FILE_NAME OnvifCommonExport.h)
target_include_directories(onvifcommon
													 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>
													 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/gsoap> $<INSTALL_INTERFACE:include>
													 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/generated> $<INSTALL_INTERFACE:include>
													 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
target_link_libraries(onvifcommon Qt5::Core)
target_compile_definitions(onvifcommon PUBLIC WITH_SELF_PIPE)
if(HAS_OPENSSL)
	target_link_libraries(onvifcommon "${OpenSSL_ssl_PATH}" "${OpenSSL_cryptro_PATH}")
endif()
if(WIN32 AND NOT BUILD_SHARED_LIBS)
	target_link_libraries(onvifcommon qtpcre2.lib version.lib Winmm.lib Netapi32.lib Userenv.lib)
endif()
target_compile_features(onvifcommon PUBLIC cxx_strong_enums cxx_auto_type cxx_nullptr cxx_long_long_type cxx_explicit_conversions)
set_target_properties(onvifcommon PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifCommonExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifcommon)
endif()

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

add_library(onvifanalytics ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifanalytics EXPORT_FILE_NAME OnvifAnalyticsExport.h)
target_link_libraries(onvifanalytics onvifcommon)
set_target_properties(onvifanalytics PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifAnalyticsExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifanalytics)
endif()

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

add_library(onvifdevice ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifdevice EXPORT_FILE_NAME OnvifDeviceExport.h)
target_link_libraries(onvifdevice onvifcommon)
set_target_properties(onvifdevice PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifDeviceExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifdevice)
endif()

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

add_library(onvifdisplay ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifdisplay EXPORT_FILE_NAME OnvifDisplayExport.h)
target_link_libraries(onvifdisplay onvifcommon)
set_target_properties(onvifdisplay PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifDisplayExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifdisplay)
endif()

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

add_library(onvifimaging ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifimaging EXPORT_FILE_NAME OnvifImagingExport.h)
target_link_libraries(onvifimaging onvifcommon)
set_target_properties(onvifimaging PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifImagingExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifimaging)
endif()

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

add_library(onvifmedia ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifmedia EXPORT_FILE_NAME OnvifMediaExport.h)
target_link_libraries(onvifmedia onvifcommon)
set_target_properties(onvifmedia PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifMediaExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifmedia)
endif()

# -------------------------------ONVIF Media2-------------------------------
set(src_files
		generated/soapMedia2BindingProxy.cpp
		#generated/soapMedia2BindingService.cpp
		OnvifMedia2Client.cpp
		)

# private header
set(private_header_files
		generated/soapMedia2BindingProxy.h
		#generated/soapMedia2BindingService.h
		)

# public header
set(public_header_files
		OnvifMedia2Client.h
		)

add_library(onvifmedia2 ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifmedia2 EXPORT_FILE_NAME OnvifMedia2Export.h)
target_link_libraries(onvifmedia2 onvifcommon)
set_target_properties(onvifmedia2 PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifMedia2Export.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifmedia2)
endif()

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

add_library(onvifptz ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifptz EXPORT_FILE_NAME OnvifPtzExport.h)
target_link_libraries(onvifptz onvifcommon)
set_target_properties(onvifptz PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifPtzExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifptz)
endif()

# -------------------------------ONVIF Event-------------------------------
set(src_files
		generated/soapPullPointSubscriptionBindingProxy.cpp
		#generated/soapPullPointSubscriptionBindingService.cpp
		OnvifEventClient.cpp
		OnvifPullPoint.cpp
		Topics.cpp
		NotificationFilter.cpp
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
		Topics.h
		NotificationFilter.h
		)

add_library(onvifevent ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifevent EXPORT_FILE_NAME OnvifEventExport.h)
target_link_libraries(onvifevent onvifcommon)
set_target_properties(onvifevent PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifEventExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifevent)
endif()

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

add_library(onvifreceiver ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifreceiver EXPORT_FILE_NAME OnvifReceiverExport.h)
target_link_libraries(onvifreceiver onvifcommon)
set_target_properties(onvifreceiver PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifReceiverExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifreceiver)
endif()

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

add_library(onvifrecording ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifrecording EXPORT_FILE_NAME OnvifRecordingExport.h)
target_link_libraries(onvifrecording onvifcommon)
set_target_properties(onvifrecording PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifRecordingExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifrecording)
endif()

# -------------------------------ONVIF Discovery-------------------------------
set(src_files
		# generated/soapRemoteDiscoveryBindingProxy.cpp
		# generated/soapRemoteDiscoveryBindingService.cpp
		# gsoap/wsddapi.c
		OnvifDiscoveryClient.cpp
		# OnvifDiscover.cpp
		OnvifDiscovery.cpp
		DiscoveryMatch.cpp
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
		OnvifDiscoveryClient.h
		DeleterDuplicator.h
		# OnvifDiscover.h
		generated/soapwsddProxy.h
		OnvifDiscovery.h
		DiscoveryMatch.h
		)

add_library(onvifdiscovery ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifdiscovery EXPORT_FILE_NAME OnvifDiscoveryExport.h)
target_link_libraries(onvifdiscovery onvifcommon)
set_target_properties(onvifdiscovery PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifDiscoveryExport.h")
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifdiscovery)
endif()

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

add_library(onvifreplay ${src_files} ${private_header_files} ${public_header_files})
generate_export_header(onvifreplay EXPORT_FILE_NAME OnvifReplayExport.h)
target_link_libraries(onvifreplay onvifcommon)
set_target_properties(onvifreplay PROPERTIES PUBLIC_HEADER "${public_header_files};${CMAKE_CURRENT_BINARY_DIR}/OnvifReplayExport.h")
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
target_link_libraries(onvifinfo onvifcommon onvifdevice onvifdiscovery onvifreplay onvifrecording onvifreceiver onvifptz onvifmedia onvifmedia2 onvifimaging onvifevent onvifdisplay onvifanalytics)
if(USE_PRECOMPILED_HEADERS)
	cotire(onvifinfo)
endif()

if(MSVC)
	set_target_properties(onvifinfo onvifcommon onvifdevice onvifdiscovery onvifreplay onvifrecording onvifreceiver onvifptz onvifmedia onvifmedia2 onvifimaging onvifevent onvifdisplay onvifanalytics PROPERTIES COMPILE_FLAGS "/bigobj")
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

configure_package_config_file("${PROJECT_SOURCE_DIR}/CMake/libONVIFConfig.cmake.in" "${PROJECT_BINARY_DIR}/libONVIFConfig.cmake" INSTALL_DESTINATION cmake
															PATH_VARS INCLUDE_INSTALL_DIR CMAKE_INSTALL_DIR BIN_INSTALL_DIR LIB_INSTALL_DIR)

write_basic_package_version_file("${PROJECT_BINARY_DIR}/libONVIFVersion.cmake" VERSION "${info.version.major}.${info.version.minor}.${info.version.patch}" COMPATIBILITY SameMajorVersion)

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
				onvifmedia2
				onvifimaging
				onvifevent
				onvifdisplay
				onvifanalytics
				EXPORT libONVIFTargets RUNTIME DESTINATION bin ARCHIVE DESTINATION lib LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include
				)

install(EXPORT libONVIFTargets DESTINATION cmake)

install(FILES "${PROJECT_BINARY_DIR}/libONVIFConfig.cmake" "${PROJECT_BINARY_DIR}/libONVIFVersion.cmake" DESTINATION cmake)
