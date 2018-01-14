cmake_minimum_required(VERSION 2.6)
project(7-1_FindChessBoardCorner)
find_package( OpenCV REQUIRED )


add_executable(7-1_FindChessBoardCorner FindChessBoardCorner.cpp)
target_link_libraries(7-1_FindChessBoardCorner ${OpenCV_LIBS})