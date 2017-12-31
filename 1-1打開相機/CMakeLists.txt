cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(1-1_OpenCamera)
find_package( OpenCV REQUIRED )


add_executable(1-1_OpenCamera OpenCamera.cpp)
target_link_libraries(1-1_OpenCamera ${OpenCV_LIBS})