cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 17) 
project( cppbeerxels ) 
find_package( OpenCV REQUIRED)

file(GLOB SOURCES
  src/*
)

include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( cppbeerxels ${SOURCES} )
target_link_libraries( cppbeerxels ${OpenCV_LIBS} )

