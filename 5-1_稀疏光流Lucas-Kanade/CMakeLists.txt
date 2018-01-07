cmake_minimum_required(VERSION 2.6)
project(5-1_SparseOpticalFlowLucasKanade)
find_package( OpenCV REQUIRED )


add_executable(5-1_SparseOpticalFlowLucasKanade SparseOpticalFlowLucasKanade.cpp)
target_link_libraries(5-1_SparseOpticalFlowLucasKanade ${OpenCV_LIBS})