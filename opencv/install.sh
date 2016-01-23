
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

# fortran / atlas / python
sudo apt-get install build-essential gfortran libatlas-base-dev python-pip python-dev

# numpy & scipy
sudo pip install --upgrade pip
sudo pip install numpy
sudo pip install scipy

# basic development environment
sudo apt-get install build-essential cmake pkg-config

# opencv dependencies. ubuntu 13.04 ships with opencv
sudo apt-get build-dep libopencv-dev

# additional dependencies for java support
sudo apt-get install default-jdk ant

# opengl support
sudo apt-get install libgtkglext1-dev

#3. Install opencv
# Download opencv
git clone https://github.com/Itseez/opencv
git checkout 3.0.0

# compile opencv
cd opencv
mkdir build
cd build

cmake -D CMAKE_BUILD_TYPE=RELEASE -D INSTALL_C_EXAMPLES=ON  -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_OPENGL=ON -D WITH_V4L=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_TBB=ON ..

# compile
make

# install
sudo make install

# configuration
LD_OPENCV="/etc/ld.so.conf.d/opencv.conf"
if [ -f $LD_OPENCV ];
then
   echo "File $LD_OPENCV exists. No action required"
else
   echo "File $LD_OPENCV does not exist."
   touch $LD_OPENCV
   echo "/usr/local/lib" >> $LD_OPENCV
   if [$SHELL == "/usr/bin/zsh"]
	echo "PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig" > ~/.zshrc
	echo "export PKG_CONFIG_PATH" > ~/.zshrc
   if [$SHELL == "/usr/bin/bash"]
	echo "PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig" > ~/.bashrc
        echo "export PKG_CONFIG_PATH" > ~/.bashrc
fi

