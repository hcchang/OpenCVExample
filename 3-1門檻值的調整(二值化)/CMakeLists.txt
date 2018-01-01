cmake_minimum_required(VERSION 2.6)
project(3-1_ImageBinaryThreshold)
find_package( OpenCV REQUIRED )


add_executable(3-1_ImageBinaryThreshold ImageBinaryThreshold.cpp)
target_link_libraries(3-1_ImageBinaryThreshold ${OpenCV_LIBS})