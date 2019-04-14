cmake_minimum_required( VERSION 2.8 )

project( CH13 )
set( OpenCV_DIR /usr/local/opencv-3.4.2/share/OpenCV/ )
find_package( OpenCV REQUIRED )

add_executable( exa1401 exa1401.cpp )
add_executable( exa1402 exa1402.cpp )
add_executable( exa1403 exa1403.cpp )

target_link_libraries( exa1401 ${OpenCV_LIBS} )
target_link_libraries( exa1402 ${OpenCV_LIBS} )
target_link_libraries( exa1403 ${OpenCV_LIBS} )