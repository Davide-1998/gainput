
project(syncsample)

set(SYNCSAMPLE_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/syncsample.cpp"
)

set(FW_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/../samplefw/SampleFramework.cpp"
)
set(FW_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/../samplefw/SampleFramework.h"
)

if(ANDROID)
	add_library(${PROJECT_NAME} SHARED ${SYNCSAMPLE_SOURCES} ${FW_SOURCES} ${FW_HEADERS})
else()
	add_executable(${PROJECT_NAME} WIN32 ${SYNCSAMPLE_SOURCES} ${FW_SOURCES} ${FW_HEADERS})
endif()

target_link_libraries(${PROJECT_NAME} gainput::gainput)

if(LINUX)
	target_link_libraries(${PROJECT_NAME} X11 GL rt)
elseif(WIN32)
	target_link_libraries(${PROJECT_NAME} ${XINPUT} ws2_32)
elseif(APPLE)
	target_link_libraries(${PROJECT_NAME} ${FOUNDATION} ${IOKIT} ${APPKIT})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../lib/include/")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../samplefw/")
