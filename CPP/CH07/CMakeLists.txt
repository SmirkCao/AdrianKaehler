cmake_minimum_required(VERSION 2.8)

project( CH07 )
set(OpenCV_DIR /usr/local/opencv-3.4.2/share/OpenCV/)
find_package( OpenCV REQUIRED )

add_executable( exa0701 exa0701.cpp )
add_executable( exe0701 exe0701.cpp )
target_link_libraries( exa0701 ${OpenCV_LIBS} )
target_link_libraries( exe0701 ${OpenCV_LIBS} )



