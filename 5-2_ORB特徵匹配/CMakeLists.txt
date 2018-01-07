cmake_minimum_required(VERSION 2.6)
project(5-1_ORBFeatureMatcher)
find_package( OpenCV REQUIRED )


add_executable(5-1_ORBFeatureMatcher ORBFeatureMatcher.cpp)
target_link_libraries(5-1_ORBFeatureMatcher ${OpenCV_LIBS})