# cppbeerxels

C++ implementation of Beerxels project (previously in Python).

This program takes in a number of pictures of bottlecaps (or any other circular object for that matter) and uses them to recreate a reference image in a pixel-art like style. 

I have been collecting bottle caps over the past few years and wanted to create art with it. 


# Installation

This project is developed on Linux (Ubuntu 20.04) and compiled with gcc 9.3.0 exclusively. If you are on a different operating system: Proceed at your own risk.

You can use the precompiled binary or compile yourself.
For local compilation, go to the project directory and first run
```
  $ cmake . 
```
and then 
```
  $ make
```
.

Don't forget to install the required depenencies.

# Dependencies

This project requires [opencv to be installed](https://docs.opencv.org/4.x/df/d65/tutorial_table_of_content_introduction.html).

The installation can sometimes be a bit tricky. Following the link above should work, but in my case I had to add a symbolic link with the command 
```
$ sudo ln -s /usr/local/include/opencv4/opencv2 /usr/local/include/opencv2
```
for the compiler to find the library. 

# Usage

This project is interfaced via the command line. 

It is imperative that the executable is run from the project directory, as relative paths are used to access the images in the data directory.

# Example Result

![reference image of a baboon](https://github.com/stlljonas/cppbeerxels/blob/README/data/reference/baboon.png?raw=true) ![recreated with bottlecaps](https://github.com/stlljonas/cppbeerxels/blob/README/data/baboon-caps.png?raw=true)

![here](https://github.com/stlljonas/cppbeerxels/blob/README/data/mona-lisa-caps.jpg?raw=true) 

A real world recreation is work in progress and will be shared here as well.
# Architecture

Dependency Diagram:
<pre>
 Hungarian
    ^
    |
 CapField-----------> Tiling
    |           |
    v           |
CapShepherd     |
    |           |
    v           |
   Cap          |
    |           |
    v           |
SmartCircle <----
    |
    v
  OpenCV
</pre>

# Current issues

The reflections in the bottle cap images likely distort their actual color, questioning how well the computational results translate into the real world. Possible solutions to this may be softer light sources or possibly scanning the bottle caps (here reflections would again have to be mitigated).

The tuning option relies on key codes returned by openCV, which seem to differ between machines. Further investigation is required. 
