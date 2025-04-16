
project(gainputtest)

set(TEST_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/test_inputdevice.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/test_inputmanager.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/test_inputmap.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/test_inputrecording.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/test_inputstate.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/test.cpp"
)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

if(ANDROID)
	add_library(${PROJECT_NAME} SHARED ${TEST_SOURCES})
else()
	add_executable(${PROJECT_NAME} WIN32 ${TEST_SOURCES})
endif()

if(APPLE AND NOT IOS)
	find_library(APPKIT AppKit)
else()
	set(APPKIT "")
endif()

target_link_libraries(${PROJECT_NAME} gainput::gainput)

if(LINUX)
	target_link_libraries(${PROJECT_NAME} X11 GL rt)
elseif(WIN32)
	target_link_libraries(${PROJECT_NAME} ${XINPUT} ws2_32)
elseif(APPLE)
	target_link_libraries(${PROJECT_NAME} ${FOUNDATION} ${IOKIT} ${APPKIT})
endif()

if(MSVC)
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
endif(MSVC)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/lib/include/")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/extern/catch/")
