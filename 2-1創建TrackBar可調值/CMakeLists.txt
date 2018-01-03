cmake_minimum_required(VERSION 2.6)
project(2-1_TrackerBarExample)
find_package( OpenCV REQUIRED )


add_executable(2-1_TrackerBarExample TrackerBarExample.cpp)
target_link_libraries(2-1_TrackerBarExample ${OpenCV_LIBS})