FROM ubuntu:18.04
RUN apt update
RUN apt install python3-opencv -y && apt-get install -y wget

RUN apt install -y build-essential cmake git pkg-config libgtk-3-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
    gfortran openexr libatlas-base-dev python3-dev python3-numpy \
    libtbb2 libtbb-dev libdc1394-22-dev

RUN mkdir ~/opencv_build && cd ~/opencv_build && git clone https://github.com/opencv/opencv.git 
RUN git clone https://github.com/opencv/opencv_contrib.git

RUN cd ~/opencv_build/opencv && mkdir build && cd build \
#   && cmake -D CMAKE_BUILD_TYPE=RELEASE \
#  -D CMAKE_INSTALL_PREFIX=/usr/local \
#  -D INSTALL_C_EXAMPLES=ON \
#  -D INSTALL_PYTHON_EXAMPLES=ON \
#  -D OPENCV_GENERATE_PKGCONFIG=ON \
#  -D OPENCV_EXTRA_MODULES_PATH=/opencv_contrib/modules \
#  -DCMAKE_CXX_FLAGS=-std=c++11 \
#  -DENABLE_PRECOMPILED_HEADERS=OFF \
#  -D BUILD_EXAMPLES=ON ..
    && cmake -DCMAKE_CXX_FLAGS=-std=c++11 \
    -DCMAKE_BUILD_TYPE=RELEASE \
    -DCMAKE_INSTALL_PREFIX=/usr/local \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_DOCS=OFF \
    -DBUILD_PERF_TESTS=OFF \
    -DBUILD_TESTS=OFF \
    -DINSTALL_C_EXAMPLES=OFF \
    -DENABLE_PRECOMPILED_HEADERS=OFF \
    -DWITH_OPENMP=ON \
    -DWITH_V4L=ON \
    -DWITH_TBB=ON \
#    -DWITH_QT=ON \
    -DWITH_OPENGL=ON \
    -DWITH_JPEG=ON \
    -DWITH_FFMPEG=ON \
    -DWITH_GSTREAMER=ON \
    -DWITH_OPENCL=ON \
    -DWITH_GPHOTO2=ON \
    -DWITH_LIBV4L=ON \
    -DINSTALL_PYTHON_EXAMPLES=ON \
    -DBUILD_SHARED_LIBS=ON \
    -DENABLE_CXX11=ON ..
#    -DOPENCV_EXTRA_MODULES_PATH=/media/feliz/Safira/GitHub/Gridkey/OpenCV/opencv_contrib-3.3.0/modules \
#    -DPYTHON_EXECUTABLE=/home/feliz/.envs/gridkey/bin/python ..

RUN cd ~/opencv_build/opencv/build \
    && make -j8 \
    && make install

RUN cd / && mkdir project
COPY doc /project
RUN cd project && ls && cmake CMakeLists.txt && make
CMD ./project/main
#CMD bash

