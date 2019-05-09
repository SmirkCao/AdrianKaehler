cmake_minimum_required( VERSION 2.8 )

project( CH20 )
set( OpenCV_DIR /usr/local/opencv-3.4.2/share/OpenCV/ )
find_package( OpenCV REQUIRED )

add_executable( exa2001 exa2001.cpp )

target_link_libraries( exa2001 ${OpenCV_LIBS} )
