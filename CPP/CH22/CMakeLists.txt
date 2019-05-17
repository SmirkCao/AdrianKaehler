cmake_minimum_required( VERSION 2.8 )

project( CH22 )
set( OpenCV_DIR /usr/local/opencv-3.4.2/share/OpenCV/ )
find_package( OpenCV REQUIRED )

add_executable( exa2201 exa2201.cpp)

target_link_libraries( exa2201 ${OpenCV_LIBS} )


