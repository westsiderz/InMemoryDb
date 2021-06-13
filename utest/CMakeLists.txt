cmake_minimum_required(VERSION 3.14)

# Include a CMake file containing helpful macros
include(${CMAKE_CURRENT_SOURCE_DIR}/../Macros.cmake)

project (InMemoryDbUnitTests)

# Get the GoogleTest libraries.
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Collect all the header and source files
ListHeaderFiles(FALSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR})
ListSourceFiles(FALSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR})

# Collect the source files of the InMemoryDb. We need to build them
# since they are not built into library but rather into executable
# so we don't have the implementations from them. We don't need all of them
# so simply will list the files we need
set(SOURCE_FILES_PROJECT ${CMAKE_CURRENT_SOURCE_DIR}/../source/DbTableTest.cpp
						 ${CMAKE_CURRENT_SOURCE_DIR}/../source/InMemoryDb.cpp
						 ${CMAKE_CURRENT_SOURCE_DIR}/../source/TimeMeasurement.cpp)

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${SOURCE_FILES_PROJECT} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
												   ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Add filters in Visual Studio to hold the source files
source_group("Header Files" FILES ${HEADER_FILES})
source_group("Source Files" FILES ${SOURCE_FILES})
source_group("Source Files/InMemoryDb" FILES ${SOURCE_FILES_PROJECT})

target_link_libraries(${PROJECT_NAME} gtest_main)