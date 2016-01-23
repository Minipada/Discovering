
#Source Code Steps For Installation

#1. Download Scipy Stack:

sudo apt-get update
sudo apt-get upgrade  
sudo apt-get install python-numpy python-scipy python-matplotlib ipython ipython- notebook python-pandas python-sympy python-nose

#2. Install environment and dependencies:

# install qt5
sudo apt-get install qt5-default 

# install libgphoto2
sudo apt-get install libgphoto2-dev

# install  tesseract
sudo apt-get install tesseract-dev

# libproto
sudo apt-get install libproto-dev

# gstreamer
sudo apt-get install gstreamer0.10-dev gstreamer0.10-plugins-bad gstreamer0.10-plugins-good gstreamer0.10-plugins-ugly

#### fortran / atlas / python
sudo apt-get install build-essential gfortran libatlas-base-dev python-pip python-dev

#### numpy & scipy
sudo pip install --upgrade pip
sudo pip install numpy
sudo pip install scipy

#### basic development environment
sudo apt-get install build-essential cmake pkg-config

#### opencv dependencies. ubuntu 13.04 ships with opencv
sudo apt-get build-dep libopencv-dev

#### additional dependencies for java support
sudo apt-get install default-jdk ant

#### opengl support
sudo apt-get install libgtkglext1-dev

###3. Install opencv
#### Download opencv
wget https://github.com/Itseez/opencv/archive/3.0.0.zip

#### unzip opencv
unzip opencv-3.0.0.zip

#### compile opencv
cd opencv-3.0.0
mkdir build
cd build

cmake -D CMAKE_BUILD_TYPE=RELEASE -D INSTALL_C_EXAMPLES=ON \  
        -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON \
        -D WITH_QT=ON -D CMAKE_INSTALL_PREFIX=/usr/local \
        -D WITH_OPENGL=ON -D WITH_V4L=ON \
        -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_TBB=ON ..

make -j $(nproc)
sudo make install
echo "DONE"`
