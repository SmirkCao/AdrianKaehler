FROM ubuntu:16.04
#MAINTAINER Smirk Cao

RUN apt-get update
# dependencies
RUN apt-get install -y apt-utils
RUN apt-get install -y build-essential 
RUN apt-get install -y cmake git libgtk2.0-dev pkg-config libavcodec-dev \
libavformat-dev libswscale-dev python-dev python-numpy libtbb2 libtbb-dev \
libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev

RUN apt-get install -y unzip vim wget

RUN cd \
    && wget https://github.com/opencv/opencv/archive/3.4.2.zip \
    && unzip 3.4.2.zip \
    && mv opencv-3.4.2 opencv
    
RUN cd \
    && wget https://github.com/opencv/opencv_contrib/archive/3.4.2.zip \
    && unzip 3.4.2.zip \
    && mv opencv_contrib-3.4.2 opencv_contrib 

RUN cd \
    && cd opencv \
    && mkdir build \
    && cd build \
    && cmake \
       -D CMAKE_BUILD_TYPE=RELEASE \
       -D CMAKE_INSTALL_PREFIX=/usr/local/opencv-3.4.2/  \
       -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
       -D WITH_TBB=ON \
       -D WITH_V4L=ON \
       -D WITH_GTK=ON \
       -D WITH_OPENGL=ON \
       -D WITH_CUDA=OFF \
       -D WITH_CUBLAS=OFF \
       -D BUILD_EXAMPLES=OFF \
       -D INSTALL_PYTHON_EXAMPLES=OFF \
       -D INSTALL_C_EXAMPLES=OFF \
       .. \
    && make -j8 \
    && make install \
    && cd

RUN cd \
   && git clone https://github.com/SmirkCao/Lihang.git 
