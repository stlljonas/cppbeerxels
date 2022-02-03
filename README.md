# cppbeerxels
C++ implementation of Beerxels project (previously in Python)


# Installation

# Dependencies
This project requires [opencv to be installed](https://docs.opencv.org/4.x/df/d65/tutorial_table_of_content_introduction.html)

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