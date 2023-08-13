cmake_minimum_required(VERSION 3.16)

Project(IRCameraDemo_02)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package( OpenCV REQUIRED )
find_package(Qt5 REQUIRED COMPONENTS Widgets)


include_directories( ${OpenCV_INCLUDE_DIRS} )
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/dynamic)


add_executable(IRCameraDemo_02 mainwindow.ui main.cpp mainwindow.cpp  util.cpp)


target_link_libraries( IRCameraDemo_02 /home/labsun/IR_02/USB_Linux_SDK_20220831/IRCameraDemo/uvc/libv4l2.so)
target_link_libraries( IRCameraDemo_02 /home/labsun/IR_02/USB_Linux_SDK_20220831/IRCameraDemo/uvc/libv4l2core.so)

target_link_libraries( IRCameraDemo_02 ${OpenCV_LIBS})
target_link_libraries( IRCameraDemo_02 Qt5::Widgets)
