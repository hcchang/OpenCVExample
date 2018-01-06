cmake_minimum_required(VERSION 2.6)
project(6-1_KalmanFIlter)
find_package( OpenCV REQUIRED )


add_executable(6-1_KalmanFIlter KalmanFIlter.cpp)
target_link_libraries(6-1_KalmanFIlter ${OpenCV_LIBS})