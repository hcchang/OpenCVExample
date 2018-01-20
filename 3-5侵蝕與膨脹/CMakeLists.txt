cmake_minimum_required(VERSION 2.6)
project(3-5_Erosion_Dilation)
find_package( OpenCV REQUIRED )


add_executable(3-5_Erosion_Dilation Erosion_Dilation.cpp)
target_link_libraries(3-5_Erosion_Dilation ${OpenCV_LIBS})