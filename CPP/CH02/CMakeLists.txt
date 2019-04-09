cmake_minimum_required(VERSION 2.8)

project( CH02 )
set(OpenCV_DIR /usr/local/opencv-3.4.2/share/OpenCV/)
find_package( OpenCV REQUIRED )

add_executable( exa0201 exa0201.cpp )

target_link_libraries( exa0201 ${OpenCV_LIBS} )


