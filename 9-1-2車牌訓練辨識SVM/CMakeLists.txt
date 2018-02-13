cmake_minimum_required(VERSION 2.6)
project(9-1-2_CarPlatTrainingSVM)
find_package( OpenCV REQUIRED )


add_executable(9-1-2_CarPlatTrainingSVM CarPlatTrainingSVM.cpp)
target_link_libraries(9-1-2_CarPlatTrainingSVM ${OpenCV_LIBS})