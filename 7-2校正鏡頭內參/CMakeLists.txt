cmake_minimum_required(VERSION 2.6)
project(7-2_CalibrateCamera)
find_package( OpenCV REQUIRED )


add_executable(7-2_CalibrateCamera CalibrateCamera.cpp)
target_link_libraries(7-2_CalibrateCamera ${OpenCV_LIBS})