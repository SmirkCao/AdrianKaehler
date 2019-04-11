cmake_minimum_required(VERSION 2.8)

project( CH11 )
set(OpenCV_DIR /usr/local/opencv-3.4.2/share/OpenCV/)
find_package( OpenCV REQUIRED )

# Compile
add_executable( exa1101 exa1101.cpp )
# add_executable( exa1102 exa1102.cpp )
# add_executable( exa1103 exa1103.cpp )

# Link
target_link_libraries( exa1101 ${OpenCV_LIBS} )
# target_link_libraries( exa1102 ${OpenCV_LIBS} )
# target_link_libraries( exa1103 ${OpenCV_LIBS} )

