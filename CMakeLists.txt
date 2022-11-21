cmake_minimum_required(VERSION 3.18)
project(MedianFilter)

set(CMAKE_CXX_STANDARD 20)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(
        Filter
        main.cpp
	filters/MedianFilterNaive.cpp 
	filters/MedianFilterHuang.cpp 
	filters/MedianFilterConst.cpp)

target_link_libraries(Filter ${OpenCV_LIBS})

