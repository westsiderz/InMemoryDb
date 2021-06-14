cmake_minimum_required(VERSION 3.14)

# Include a CMake file containing helpful macros
include(${CMAKE_CURRENT_SOURCE_DIR}/Macros.cmake)

project (InMemoryDb)

# Collect all the header and source files
ListHeaderFiles(FALSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR})
ListSourceFiles(FALSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR})

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add filters in Visual Studio to hold the source files
source_group("Header Files" FILES ${HEADER_FILES})
source_group("Source Files" FILES ${SOURCE_FILES})

# Add compiler options for Visual Studio
if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE 	/std:c++17
													/Wall
													/WX
													/wd4710
													/wd4711
													/wd4820
													/wd5045)
	
	target_compile_definitions(${PROJECT_NAME} PRIVATE
													__STDC_WANT_SECURE_LIB__)
#Add compiler options for Clang and GCC
else()
    target_compile_options(${PROJECT_NAME} PRIVATE 	-Wall
													-Wextra
													-Wpedantic
													-Werror)

endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utest)

