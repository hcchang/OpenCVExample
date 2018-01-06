cmake_minimum_required(VERSION 2.6)
project(3-2_AddPatternToImage)
find_package( OpenCV REQUIRED )


add_executable(3-2_AddPatternToImage AddPatternToImage.cpp)
target_link_libraries(3-2_AddPatternToImage ${OpenCV_LIBS})