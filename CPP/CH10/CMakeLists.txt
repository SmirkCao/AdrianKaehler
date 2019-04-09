cmake_minimum_required(VERSION 2.8)

project( CH10 )
set(OpenCV_DIR /usr/local/opencv-3.4.2/share/OpenCV/)
find_package( OpenCV REQUIRED )

# Compile
add_executable( exa1001 exa1001.cpp )
add_executable( exa1002 exa1002.cpp )
add_executable( exa1003 exa1003.cpp )

# Link
target_link_libraries( exa1001 ${OpenCV_LIBS} )
target_link_libraries( exa1002 ${OpenCV_LIBS} )
target_link_libraries( exa1003 ${OpenCV_LIBS} )

