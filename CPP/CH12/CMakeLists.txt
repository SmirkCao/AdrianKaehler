cmake_minimum_required(VERSION 2.8)

project( CH11 )
set(OpenCV_DIR /usr/local/opencv-3.4.2/share/OpenCV/)
find_package( OpenCV REQUIRED )

# Compile
add_executable( exa1201 exa1201.cpp )
add_executable( exa1202 exa1202.cpp )

# Link
target_link_libraries( exa1201 ${OpenCV_LIBS} )
target_link_libraries( exa1202 ${OpenCV_LIBS} )

