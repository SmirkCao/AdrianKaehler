cmake_minimum_required(VERSION 2.8)

project( examples )
set(OpenCV_DIR /usr/local/opencv-3.4.2/share/OpenCV/)
find_package( OpenCV REQUIRED )

find_package( OpenGL )

if(OPENGL_FOUND)
  include_directories( ${OpenCV_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} )
else()
  include_directories( ${OpenCV_INCLUDE_DIRS} )
endif()

add_executable( helloword helloword.cpp )

target_link_libraries( helloword ${OpenCV_LIBS} )


