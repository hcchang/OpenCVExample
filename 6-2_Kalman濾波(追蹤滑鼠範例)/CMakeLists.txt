cmake_minimum_required(VERSION 2.6)
project(6-2_KalmanFIlterTrackingMouse)
find_package( OpenCV REQUIRED )


add_executable(6-2_KalmanFIlterTrackingMouse KalmanFIlterTrackingMouse.cpp)
target_link_libraries(6-2_KalmanFIlterTrackingMouse ${OpenCV_LIBS})