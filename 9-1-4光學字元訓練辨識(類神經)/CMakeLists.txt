cmake_minimum_required(VERSION 2.6)
project(9-1-4_OpticalCharacterTrainAndRecognitionANN)
find_package( OpenCV REQUIRED )


add_executable(9-1-4_OpticalCharacterTrainAndRecognitionANN OpticalCharacterTrainAndRecognitionANN.cpp)
target_link_libraries(9-1-4_OpticalCharacterTrainAndRecognitionANN ${OpenCV_LIBS})