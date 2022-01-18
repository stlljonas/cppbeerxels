#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include<opencv2/opencv.hpp>

struct Circle {
    int radius;
    // x equals width, left to right, equals cols
    // y equals height, top to bottom, equals rows
    cv::Point center;
    cv::Mat regionOfInterest(cv::Mat image);
};

#endif /* _CIRCLE_H_ */
