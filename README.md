# cppbeerxels
C++ implementation of Beerxels project (previously in Python)


# Installation

This project is developed and tested on Linux exclusively.

If you are on a different operating system: Proceed at your own risk.

# Dependencies

This project requires [opencv to be installed](https://docs.opencv.org/4.x/df/d65/tutorial_table_of_content_introduction.html).

The installation can sometimes be a bit tricky, on linux. Following the link above should work, but in my case I had to add a symbolic link with the command 
'''
	$ sudo ln -s /usr/local/include/opencv4/opencv2 /usr/local/include/opencv2
'''
for the compiler to find the library. 

# Usage

# Example Result

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