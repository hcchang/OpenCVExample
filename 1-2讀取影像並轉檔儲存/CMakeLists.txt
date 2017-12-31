cmake_minimum_required(VERSION 2.6)
project(1-2_LoadImageAndSave)
find_package( OpenCV REQUIRED )


add_executable(1-2_LoadImageAndSave LoadImageAndSave.cpp)
target_link_libraries(1-2_LoadImageAndSave ${OpenCV_LIBS})