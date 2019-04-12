cmake_minimum_required( VERSION 2.8 )

project( CH13 )
set( OpenCV_DIR /usr/local/opencv-3.4.2/share/OpenCV/ )
find_package( OpenCV REQUIRED )

add_executable( exa1301 exa1301.cpp )

target_link_libraries( exa1301 ${OpenCV_LIBS} )
