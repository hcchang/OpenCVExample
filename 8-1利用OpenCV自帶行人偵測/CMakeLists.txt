cmake_minimum_required(VERSION 2.6)
project(8-1_OpenCVPeopleDetect)
find_package( OpenCV REQUIRED )


add_executable(8-1_OpenCVPeopleDetect OpenCVPeopleDetect.cpp)
target_link_libraries(8-1_OpenCVPeopleDetect ${OpenCV_LIBS})