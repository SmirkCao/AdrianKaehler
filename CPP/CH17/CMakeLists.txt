cmake_minimum_required( VERSION 2.8 )

project( CH17 )
set( OpenCV_DIR /usr/local/opencv-3.4.2/share/OpenCV/ )
find_package( OpenCV REQUIRED )

add_executable( exa1701 exa1701.cpp )

target_link_libraries( exa1701 ${OpenCV_LIBS} )
