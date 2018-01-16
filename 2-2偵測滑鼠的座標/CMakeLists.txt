cmake_minimum_required(VERSION 2.6)
project(2-2_DetecMouseCoordinate)
find_package( OpenCV REQUIRED )

add_executable(2-2_DetecMouseCoordinate DetecMouseCoordinate.cpp)
target_link_libraries(2-2_DetecMouseCoordinate ${OpenCV_LIBS})