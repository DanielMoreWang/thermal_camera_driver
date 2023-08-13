cmake_minimum_required(VERSION 3.16)

Project(Video_Capture)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( OpenCV REQUIRED )

add_executable(Video_Capture video_capture.cpp)

target_link_libraries( Video_Capture ${OpenCV_LIBS})