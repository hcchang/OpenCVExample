cmake_minimum_required(VERSION 2.6)
project(9-1-3_OpticalCharacterSegment)
find_package( OpenCV REQUIRED )


add_executable(9-1-3_OpticalCharacterSegment OpticalCharacterSegment.cpp)
target_link_libraries(9-1-3_OpticalCharacterSegment ${OpenCV_LIBS})