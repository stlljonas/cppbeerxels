#include "Cap.h"

void Cap::_cutOutBottleCap() {
    // Load image
    cv::Mat sourceImage = cv::imread(sourceImagePath);
    // Preprocess for circle detection
    double scalingFactor = 0.25;
    cv::Mat image;
    cv::resize(sourceImage,sourceImage, cv::Size(), scalingFactor, scalingFactor);
    cv::medianBlur(sourceImage, image, blurAperture);
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY); 

    // Detect Circle 
    _detectCircle(image);

    // Crop image to circle
    cv::Rect range = _circleRegionOfInterest(image);
    cv::Mat croppedImage = sourceImage(range);
    popUpImage(croppedImage);
    
    // Create circular mask
    cv::Mat mask = cv::Mat::zeros(croppedImage.rows,croppedImage.cols, CV_8U);
    cv::circle(mask, cv::Point(circle.radius,circle.radius),circle.radius,cv::Scalar::all(1),-1);
    
    // Apply mask / black out background
    croppedImage.copyTo(BottleCap,mask);

    popUpImage(BottleCap);
}

cv::Mat Cap::getBottleCap() {
    // todo try to load it from file
    _cutOutBottleCap();
    return BottleCap; // temp   
    
    // call cutOutBottleCap()
    // save cutout to file
    // cv::imwrite()
}

void Cap::_detectCircle(cv::Mat image) {
    std::vector<cv::Vec3f> circlesFloat;
    cv::HoughCircles(image, circlesFloat, cv::HOUGH_GRADIENT, 1.5, 50, 100, 100, 20);
    std::cout << circlesFloat.size() << " circles found" << std::endl;
    std::vector<cv::Vec3i> circlesInt = vectorOfVec3FloatToInt(circlesFloat);
    cv::Mat tempImage;
    image.copyTo(tempImage);
    drawHoughCircles(tempImage, circlesInt);
    popUpImage(tempImage);
    // circlesInt is sorted by highest rating -> circlesInt[0] should be the most prominent circle detected
    circle.center.x = circlesInt[0][0];
    circle.center.y = circlesInt[0][1];
    circle.radius = circlesInt[0][2];
}

cv::Rect Cap::_circleRegionOfInterest(cv::Mat image) {
    int& x = circle.center.x;
    int& y = circle.center.y;
    int& r = circle.radius;
    cv::Rect boundingRect(x-r, y-r, r*2,r*2); 
    return boundingRect;
}