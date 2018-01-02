cmake_minimum_required(VERSION 2.6)
project(4-1_CannyEdgeDetection)
find_package( OpenCV REQUIRED )


add_executable(4-1_CannyEdgeDetection CannyEdgeDetection.cpp)
target_link_libraries(4-1_CannyEdgeDetection ${OpenCV_LIBS})