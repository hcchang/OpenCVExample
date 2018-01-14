cmake_minimum_required(VERSION 2.6)
project(5-2_ORBFeatureMatcher)
find_package( OpenCV REQUIRED )


add_executable(5-2_ORBFeatureMatcher ORBFeatureMatcher.cpp)
target_link_libraries(5-2_ORBFeatureMatcher ${OpenCV_LIBS})