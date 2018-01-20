cmake_minimum_required(VERSION 2.6)
project(3-4_FilterExample)
find_package( OpenCV REQUIRED )


add_executable(3-4_FilterExample FilterExample.cpp)
target_link_libraries(3-4_FilterExample ${OpenCV_LIBS})