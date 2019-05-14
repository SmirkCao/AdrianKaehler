cmake_minimum_required( VERSION 2.8 )

project( CH21 )
set( OpenCV_DIR /usr/local/opencv-3.4.2/share/OpenCV/ )
find_package( OpenCV REQUIRED )

add_executable( exa2101 exa2101.cpp )
add_executable( exa2102 exa2102.cpp )


target_link_libraries( exa2101 ${OpenCV_LIBS} )
target_link_libraries( exa2102 ${OpenCV_LIBS} )

