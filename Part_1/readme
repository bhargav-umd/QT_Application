# Software Assessment Part 1

Aim of program is to show a graphic user interface capableof digitizing circles. GUI should start with single window containing a grid of 20x20 blocks.All points should start out grey.  The user can then click to place the center of a circle, and then drag to set its radius, similar to various graphics programs.  The circle should be drawn on the screen.When the user releases the mouse button, the program should highlight the points (make them blue) that correspond to the edge of the circle, in a way such that the points could be connected to reconstruct the circle.Then, two additional circles should be created corresponding to the largest and smallest radius of the highlighted points.


## Prerequisite and Dependancies
- QtIvi Unix system Application Manager
- install Qt Creator

### To Install qt-5 in linux system
Use "https://doc.qt.io/qt-5/gettingstarted.html" for procedural instructions.


## How to Build and Run the Part_1 program

1. Using Qt Creator IDE  
Goto File->Open Project -> Browse for Part_1.pro file and select it -> Press Ctrl+R to build and run the program -> Program will show a gui -> Click and drag to draw a circle of choice on the blocks

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
./Part_1

```

## Approach

=> Using Qpainter to show a gui with 20 blocks with a gap of 20 and size of 10x10.
=> Created methods for mouse related events such as 
	-Mouse press event which finds the location of mouse click and stores it as center of the circle.
	-Mouse Move event which shows the dynamic circles of different radii
	 as user moves the mouse around of the gui.
	- Mouse Release Event -As soon as mouse is released, we register the circle dimension and 
	path which intersects the our blocks and based on them we draw 2 additional circles.

## Documentation

Already generated DOxygen config file in Documentation folder using 
```
doxygen <doxygen config file name>
```
Edited Project Name,description and input files 

To generate Doxygen Documentation in HTML and LaTEX, follow the next steps:

```
cd Documentation
doxygen doxyconfig
```

Use file Explorer and Open html/index.html file to see the documentation in web browser.
