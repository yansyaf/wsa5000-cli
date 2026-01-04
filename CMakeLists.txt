# CMake configuration for wsa5000-cli

cmake_minimum_required(VERSION 3.18)
project(wsa5000-cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force 32-bit build on Windows for x86 DLL compatibility
if(WIN32)
	if(NOT CMAKE_GENERATOR_PLATFORM)
		set(CMAKE_GENERATOR_PLATFORM x86 CACHE STRING "Platform for generator" FORCE)
	endif()
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Source files
set(SOURCES
	main.cpp
)

# Include directories
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/rtsa/include
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link RTSA library (Windows)
if(WIN32)
	target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/rtsa/lib)
	target_link_libraries(${PROJECT_NAME} PRIVATE wsaInterface)
	# Copy DLL to output dir for convenience
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			${CMAKE_CURRENT_SOURCE_DIR}/rtsa/lib/wsaInterface.dll
			$<TARGET_FILE_DIR:${PROJECT_NAME}>
	)
endif()