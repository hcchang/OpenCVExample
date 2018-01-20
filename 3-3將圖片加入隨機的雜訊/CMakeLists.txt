cmake_minimum_required(VERSION 2.6)
project(3-3_AddRandomNoise)
find_package( OpenCV REQUIRED )


add_executable(3-3_AddRandomNoise AddRandomNoise.cpp)
target_link_libraries(3-3_AddRandomNoise ${OpenCV_LIBS})