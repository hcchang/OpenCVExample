cmake_minimum_required(VERSION 2.6)
project(4-3_DiscreteFourierTransform)
find_package( OpenCV REQUIRED )


add_executable(4-3_DiscreteFourierTransform DiscreteFourierTransform.cpp)
target_link_libraries(4-3_DiscreteFourierTransform ${OpenCV_LIBS})