#
# CMake requirements
#
# CMake 3.25 required due to variables like LINUX being available since then
cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

#
# Project Definition
#
project(gainput
	VERSION 2.0.0
	LANGUAGES CXX
	DESCRIPTION "C++ gaming input library"
)

#
# Project settings
#
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_DEBUG_POSTFIX d)

#
# CMake functionalities includes
#
include(CMakeDependentOption)

#
# Project variables
#
set(GAINPUT_TARGET_PLATFORM "${CMAKE_SYSTEM_NAME}" CACHE STRING "Platform to build gainput for (QuestVR,Linux,Android,Windows,Darwin,TVOS,iOS,NX64,ORBIS,PROSPERO")

option(BUILD_SHARED_LIBS "Build as shared lib" OFF)
option(GAINPUT_SAMPLES "Build Samples for Gainput" ON)
option(GAINPUT_TESTS "Build Tests for Gainput" ${PROJECT_IS_TOP_LEVEL})
cmake_dependent_option(GAINPUT_ENABLE_HID "Enable HID support (cmake port works only with Linux atm)" ON "NOT WIN32" ON)
cmake_dependent_option(GAINPUT_ENABLE_IOS_HAPTICS "Enable haptics on iOS" ON "APPLE OR DARWIN" OFF)

#
# Dependencies
#
include(FetchContent)
if(GAINPUT_ENABLE_HID)
	FetchContent_Declare(
		hidapi
		GIT_REPOSITORY https://github.com/libusb/hidapi.git
		GIT_TAG hidapi-0.14.0
		SYSTEM
	)
	FetchContent_MakeAvailable(hidapi)
endif()

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
set(_DUMB_VARS "GAINPUT_TARGET_PLATFORM;GAINPUT_SAMPLES;GAINPUT_TESTS;GAINPUT_ENABLE_HID")

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

