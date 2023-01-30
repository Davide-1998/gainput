cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

project(gainput)

set(GAINPUT_MAJOR_VERSION 2)
set(GAINPUT_MINOR_VERSION 0)
set(GAINPUT_PATCH_VERSION 0)
set(GAINPUT_VERSION ${GAINPUT_MAJOR_VERSION}.${GAINPUT_MINOR_VERSION}.${GAINPUT_PATCH_VERSION})

set(GAINPUT_TARGET_PLATFORM "${CMAKE_SYSTEM_NAME}" CACHE STRING "Platform to build gainput for (QuestVR,Linux,Android,Windows,Darwin,TVOS,iOS,NX64,ORBIS,PROSPERO")

option(GAINPUT_SAMPLES "Build Samples for Gainput" OFF)
option(GAINPUT_TESTS "Build Tests for Gainput" OFF)
option(GAINPUT_BUILD_STATIC "Build as static library" ON)
option(GAINPUT_ENABLE_IOS_HAPTICS "enable haptics on iOS" ON)
option(GAINPUT_ENABLE_HID "enable HID support (cmake port works only with Linux atm)" OFF)

if(!WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
else()
	set(XINPUT "Xinput9_1_0")
	if ( ${CMAKE_SYSTEM_VERSION} LESS 6.1 )
		set(XINPUT, "xinput")
	endif()
endif()

if(ANDROID)
	include(extern/cmake/AndroidNdkModules.cmake)
	android_ndk_import_module_native_app_glue()
endif()

# Dumb options
set(_DUMB_VARS "GAINPUT_TARGET_PLATFORM;GAINPUT_SAMPLES;GAINPUT_TESTS;GAINPUT_BUILD_STATIC;GAINPUT_ENABLE_HID")

message("")
message(STATUS "The following options have been set:")
foreach(_VAR ${_DUMB_VARS})
    message(STATUS "${_VAR}: ${${_VAR}}")
endforeach()
message("")

add_subdirectory(lib)

if(GAINPUT_SAMPLES)
	add_subdirectory(samples)
endif()

if(GAINPUT_TESTS)
	add_subdirectory(test)
endif()

