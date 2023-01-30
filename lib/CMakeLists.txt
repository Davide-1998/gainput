project(gainput)
message(STATUS "GAINPUT version ${GAINPUT_VERSION}")

set(CMAKE_MACOSX_RPATH 1)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -Wall -Wextra -pedantic -Wshadow -Wno-variadic-macros")
endif()

if (GAINPUT_ENABLE_HID)
  find_package(HIDAPI REQUIRED)
  if (NOT HIDAPI_FOUND)
    message(SEND_ERROR "HIDAPI not found.")
  endif ()
endif ()

set(GAINPUT_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/GainputAllocator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/GainputInputDeltaState.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/GainputInputDevice.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/GainputInputManager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/GainputInputMap.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/GainputInputState.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/GainputMapFilters.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/builtin/GainputInputDeviceBuiltIn.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/dev/GainputDev.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/dev/GainputMemoryStream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/dev/GainputNetAddress.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/dev/GainputNetConnection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/dev/GainputNetListener.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/gainput.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/gestures/GainputButtonStickGesture.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/gestures/GainputDoubleClickGesture.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/gestures/GainputHoldGesture.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/gestures/GainputPinchGesture.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/gestures/GainputRotateGesture.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/gestures/GainputSimultaneouslyDownGesture.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/gestures/GainputTapGesture.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/keyboard/GainputInputDeviceKeyboard.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/keyboard/GainputInputDeviceKeyboardMac.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/mouse/GainputInputDeviceMouse.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/pad/GainputInputDevicePad.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/pad/GainputInputDevicePadMac.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/recorder/GainputInputPlayer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/recorder/GainputInputRecorder.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/recorder/GainputInputRecording.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/touch/GainputInputDeviceTouch.cpp
)

set(GAINPUT_APPLE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/GainputIos.mm
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/GainputMac.mm
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/builtin/GainputInputDeviceBuiltInIos.mm
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/mouse/GainputInputDeviceMouseMac.mm
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/mouse/GainputInputDeviceMouseMacRaw.mm
  ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/pad/GainputInputDevicePadIos.mm
)

if (("${GAINPUT_TARGET_PLATFORM}" MATCHES "QuestVR") OR ("${GAINPUT_TARGET_PLATFORM}" MATCHES "Android"))
  set(GAINPUT_FILES 
    ${GAINPUT_FILES}   
    ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/touch/GainputInputDeviceGestureDetectorAndroid.cpp
  )
elseif ("${GAINPUT_TARGET_PLATFORM}" MATCHES "Linux")
  if (GAINPUT_ENABLE_HID)
    set(GAINPUT_FILES 
      ${GAINPUT_FILES}   
      ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/timer/GainputTimer.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/timer/GainputTimerLinux.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/GainputHID.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/GainputHIDWhitelist.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/hidparsers/HIDParserPS4Controller.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/hidparsers/HIDParserPS5Controller.cpp
      )
  endif ()
elseif ("${GAINPUT_TARGET_PLATFORM}" MATCHES "NX64")
  # Nintendo 64
elseif ("${GAINPUT_TARGET_PLATFORM}" MATCHES "Windows")
  if (GAINPUT_ENABLE_HID)
    set(GAINPUT_FILES 
      ${GAINPUT_FILES}   
      ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/timer/GainputTimer.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/timer/GainputTimerWindows.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/GainputHID.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/GainputHIDWhitelist.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/hidparsers/HIDParserPS4Controller.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/hidparsers/HIDParserPS5Controller.cpp
    )
  endif ()
elseif (("${GAINPUT_TARGET_PLATFORM}" MATCHES "TVOS") OR ("${GAINPUT_TARGET_PLATFORM}" MATCHES "iOS") OR ("${GAINPUT_TARGET_PLATFORM}" MATCHES "Darwin"))
  set(GAINPUT_FILES
    ${GAINPUT_FILES}
    ${GAINPUT_APPLE_FILES}
  )
elseif ("${GAINPUT_TARGET_PLATFORM}" MATCHES "ORBIS")
  # PS4
  set(GAINPUT_FILES 
    ${GAINPUT_FILES}  
    ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/hidparsers/HIDParserPS4Controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/hidparsers/HIDParserPS5Controller.cpp
  )

elseif ("${GAINPUT_TARGET_PLATFORM}" MATCHES "PROSPERO")
  # PS5
  set(GAINPUT_FILES 
    ${GAINPUT_FILES}  
    ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/hidparsers/HIDParserPS4Controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/gainput/hid/hidparsers/HIDParserPS5Controller.cpp
  )
endif ()

if (GAINPUT_BUILD_STATIC)
  message(STATUS "..Building static libraries (-DGAINPUT_BUILD_STATIC=OFF to build a shared lib)")
  add_library(${PROJECT_NAME} STATIC ${GAINPUT_FILES})
  set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX d FOLDER gainput) 
else ()
  message(STATUS "..Building shared libraries (-DGAINPUT_BUILD_SHARED=ON to build a static lib)")
  add_library(${PROJECT_NAME} SHARED ${GAINPUT_FILES})
  set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME gainput
    DEBUG_POSTFIX d
    VERSION ${GAINPUT_VERSION}
    SOVERSION ${GAINPUT_MAJOR_VERSION}
    FOLDER gainput
  )
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(install_libs ${install_libs} gainput)

if ("${GAINPUT_TARGET_PLATFORM}" MATCHES "QuestVR")
	set(${PROJECT_NAME}_DEFINES ${GAINPUT_DEFINES} GAINPUT_PLATFORM_QUEST)
  target_link_libraries(${PROJECT_NAME} PUBLIC native_app_glue log android)

elseif ("${GAINPUT_TARGET_PLATFORM}" MATCHES "Android")
	set(${PROJECT_NAME}_DEFINES ${GAINPUT_DEFINES} GAINPUT_PLATFORM_ANDROID)
  target_link_libraries(${PROJECT_NAME} PUBLIC native_app_glue log android)

elseif ("${GAINPUT_TARGET_PLATFORM}" MATCHES "Linux")
	set(${PROJECT_NAME}_DEFINES ${GAINPUT_DEFINES} GAINPUT_PLATFORM_LINUX)

  if (GAINPUT_ENABLE_HID)
    target_link_libraries(${PROJECT_NAME} PUBLIC HIDAPI::hidapi)
  endif ()

elseif ("${GAINPUT_TARGET_PLATFORM}" MATCHES "NX64")
  # Nintendo 64
	set(${PROJECT_NAME}_DEFINES ${GAINPUT_DEFINES} GAINPUT_PLATFORM_NX64 "GAINPUT_LIB_DYNAMIC=1")
  target_link_libraries(${PROJECT_NAME} PUBLIC Xinput9_1_0 ws2_32)

elseif ("${GAINPUT_TARGET_PLATFORM}" MATCHES "Windows")
	set(${PROJECT_NAME}_DEFINES ${GAINPUT_DEFINES} GAINPUT_PLATFORM_NX64 "GAINPUT_LIB_DYNAMIC=1")
  target_link_libraries(${PROJECT_NAME} PUBLIC Xinput9_1_0 ws2_32 HIDAPI::hidapi)

elseif ("${GAINPUT_TARGET_PLATFORM}" MATCHES "TVOS")
  # AppleTV
	set(${PROJECT_NAME}_DEFINES ${GAINPUT_DEFINES} GAINPUT_PLATFORM_TVOS)
	find_library(FOUNDATION Foundation)
	find_library(IOKIT IOKit)
  find_library(GAME_CONTROLLER GameController)
  find_library(UIKIT UIKit)
  find_library(COREMOTION CoreMotion)
  find_library(QUARTZCORE QuartzCore)
	target_link_libraries(${PROJECT_NAME} PUBLIC ${FOUNDATION} ${IOKIT} ${GAME_CONTROLLER} ${UIKIT} ${COREMOTION})

elseif ("${GAINPUT_TARGET_PLATFORM}" MATCHES "iOS")
	set(${PROJECT_NAME}_DEFINES ${GAINPUT_DEFINES} GAINPUT_PLATFORM_IOS)
	if (${PROJECT_NAME}_ENABLE_IOS_HAPTICS MATCHES ON)
		set(${PROJECT_NAME}_DEFINES ${GAINPUT_DEFINES} GAINPUT_IOS_HAPTICS)
	endif ()

	find_library(FOUNDATION Foundation)
	find_library(IOKIT IOKit)
  find_library(GAME_CONTROLLER GameController)
  find_library(UIKIT UIKit)
  find_library(COREMOTION CoreMotion)
  find_library(QUARTZCORE QuartzCore)
	target_link_libraries(${PROJECT_NAME} PUBLIC ${FOUNDATION} ${IOKIT} ${GAME_CONTROLLER} ${UIKIT} ${COREMOTION})

elseif ("${GAINPUT_TARGET_PLATFORM}" MATCHES "Darwin")
	set(${PROJECT_NAME}_DEFINES ${GAINPUT_DEFINES} GAINPUT_PLATFORM_MAC)

	find_library(FOUNDATION Foundation)
	find_library(IOKIT IOKit)
  find_library(GAME_CONTROLLER GameController)
  find_library(APPKIT AppKit)
	target_link_libraries(${PROJECT_NAME} PUBLIC ${FOUNDATION} ${IOKIT} ${GAME_CONTROLLER} ${APPKIT})

elseif ("${GAINPUT_TARGET_PLATFORM}" MATCHES "ORBIS")
  # PS4
	set(${PROJECT_NAME}_DEFINES ${GAINPUT_DEFINES} GAINPUT_PLATFORM_ORBIS)

elseif ("${GAINPUT_TARGET_PLATFORM}" MATCHES "PROSPERO")
  # PS5
	set(${PROJECT_NAME}_DEFINES ${GAINPUT_DEFINES} GAINPUT_PLATFORM_PROSPERO)
endif ()

target_compile_definitions(${PROJECT_NAME} PUBLIC ${GAINPUT_DEFINES})

# Library installation directory
if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR lib)
endif(NOT DEFINED CMAKE_INSTALL_LIBDIR)
set(libdir ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

install(
    DIRECTORY "include/gainput"
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.h"
)

install(
    TARGETS ${install_libs}
    LIBRARY DESTINATION "${libdir}"
    ARCHIVE DESTINATION "${libdir}"
    RUNTIME DESTINATION "bin"
)
