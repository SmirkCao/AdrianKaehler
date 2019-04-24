cmake_minimum_required( VERSION 2.8 )

project( CH16 )
set( OpenCV_DIR /usr/local/opencv-3.4.2/share/OpenCV/ )
find_package( OpenCV REQUIRED )

add_executable( exa1601 exa1601.cpp )

target_link_libraries( exa1601 ${OpenCV_LIBS} )
