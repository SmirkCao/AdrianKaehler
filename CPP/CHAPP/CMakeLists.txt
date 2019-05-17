cmake_minimum_required( VERSION 2.8 )

project( CHAPP )
set( OpenCV_DIR /usr/local/opencv-3.4.2/share/OpenCV/ )
find_package( OpenCV REQUIRED )

add_executable( exeapp01 exeapp01.cpp)

target_link_libraries( exeapp01 ${OpenCV_LIBS} )


