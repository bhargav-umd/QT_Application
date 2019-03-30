# Software Assessment Part 2

Aim of the Part_2 is to let user select blocks on gui and generate circle and/or ellipse from the selected points.

## Prerequisite and Dependancies
- Qt >= 5.5 QtIvi Unix system Application Manager
- install Qt Creator
- OpenCV installed in the system
- NEED openCV only for generating ellipse 

### To Install qt-5 in linux system
Use "https://doc.qt.io/qt-5/gettingstarted.html" for procedural instructions.


### To Install OpenCV into the System
To install OpenCV 3.4.0, follow the next steps in terminal:

```
sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
cd ~/<my_working_directory>
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
cd ~/opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j$(nproc)
sudo make install
sudo /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
```
### To install dependacies on windows

Follow "https://www.learnopencv.com/install-opencv3-on-windows/" to install OpenCV3 into windows


Respective changes has been made in part_2.pro file to include all the dependancies

## How to Build and Run the Part_2 program

1. Using Qt Creator IDE  
Goto File->Open Project -> Browse for Part_2.pro file and select it -> Press Ctrl+R to build and run the program -> Program will show the output gui

2. Using Terminal

### To build
```
cd <Path to Repository>
mkdir build
cd build
qmake ..
make 
sudo make install
```

### To run
```
./Part_2

```

## Approach

=> Using Qpainter to show a gui with 20 blocks with a gap of 20 and size of 10x10.
=> Created Mouse events similar to Part1, instead of storing center of circle here we store the clicks location and change color of the 
   block on the gui to register as point.
=> Store all the points until are_all_points_selected flag is set to true.
=> Program has two features 
	- Generate Circle based on the selected points.
	- Generate Ellipse based on the selected points.
### Circle Generation

Created separate Pushbutton to generate circle. Here, Circle is generated using Kasa Fit Alogorithm(the simplest and fastest fit, but biased toward smaller circles when an incomplete arc is observed), Kasa Algorithm has the following properties:

1. It is more advantageous to minimize not the mean squares.
2. The Kasa procedure gives biased estimates of the circle center unless the data are symmetrically distributed around the circumference of the circle.
3. The bias is small and tends to 0 as the number of data points approaches infinity, i.e., the estimation is consistent. The accuracy obtained is related to the arc.
length and to the noise present in the data.
4. Arcs with larger radii fit more closely to the data than those with smaller radii.

References :
1. I. Kasa, A curve fitting procedure and its error analysis, IEEE Trans. Inst.
Meas. 25, 1976, 8–14
2. https://www.cerias.purdue.edu/assets/pdf/bibtex_archive/JEI000179.pdf

### Ellipse Generation 
=> Ellipse is generated using inbuilt OpenCV funtion FitEllipse which intakes points and outputs the rotated rectangle mid point and
   width/height of the rectangle which encloses the required ellipse. We can use this rectangle properties to generate the required ellipse.
   The only limitation is,it needs atleast 5 points to generate ellipse. Created a Seperate Push Button on gui which uses this function to
   generate ellipse.  


## Documentation

Already generated Doxygen config file in Documentation folder using 
```
doxygen <doxygen config file name>
```
Edited Project Name,description and input files at respective places.

To generate Doxygen Documentation in HTML and LaTEX, follow these steps:

```
cd <Path to repository>
cd Documentation
doxygen doxyconfig
```

Use file Explorer and Open html/index.html file to see the doxygen documentation in web browser.
