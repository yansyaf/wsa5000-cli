

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


# Set Qt5_DIR or CMAKE_PREFIX_PATH if not already set (user may override)
set(QT5_INSTALL_PREFIX "C:/Qt/Qt5.12.12/5.12.12/msvc2017" CACHE PATH "Path to Qt5 installation")
if(NOT Qt5_DIR)
	set(Qt5_DIR "${QT5_INSTALL_PREFIX}/lib/cmake/Qt5" CACHE PATH "Qt5Config.cmake directory")
endif()
list(APPEND CMAKE_PREFIX_PATH "${QT5_INSTALL_PREFIX}")

# Find Qt5 Core (for CLI, no GUI)
find_package(Qt5 5.12.12 REQUIRED COMPONENTS Core)

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

# Link Qt5::Core
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)

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