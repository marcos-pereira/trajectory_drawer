cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
project (Drawer)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# add the include path to find the .h files and also OpenCV_INCLUDE_DIRS
include_directories (${CMAKE_BINARY_DIR}
		     ${CMAKE_SOURCE_DIR}
		     )

set (SRCS ${SRCS} 
		Draw.cpp
		Drawer.cpp
		Drawer.h
	)

add_library(DrawLibs ${SRCS})

add_executable (Draw Drawer.cpp)

target_link_libraries (Draw DrawLibs ${OpenCV_LIBS})

# add the install targets
install (TARGETS Draw DESTINATION bin)
