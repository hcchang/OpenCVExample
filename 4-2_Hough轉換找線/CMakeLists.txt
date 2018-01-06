cmake_minimum_required(VERSION 2.6)
project(4-2_HoughFindLine)
find_package( OpenCV REQUIRED )


add_executable(4-2_HoughFindLine HoughFindLine.cpp)
target_link_libraries(4-2_HoughFindLine ${OpenCV_LIBS})