cmake_minimum_required(VERSION 2.6)
project(3-6_ImageEqualHistogram)
find_package( OpenCV REQUIRED )


add_executable(3-6_ImageEqualHistogram ImageEqualHistogram.cpp)
target_link_libraries(3-6_ImageEqualHistogram ${OpenCV_LIBS})