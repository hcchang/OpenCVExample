cmake_minimum_required(VERSION 2.6)
project(9-1-1_CarPlatSegment)
find_package( OpenCV REQUIRED )


add_executable(9-1-1_CarPlatSegment CarPlatSegment.cpp)
target_link_libraries(9-1-1_CarPlatSegment ${OpenCV_LIBS})