#include "Cap.h"

void Cap::analyze() {
    _cutOutBottleCap();
    _computeAverageColor();
    // still need to save computation
}

cv::Mat Cap::getBottleCap() const {
    return _bottleCap;
}

cv::Scalar Cap::getAverageColor() const {
    return _averageColor;
}

void Cap::_detectCircle(cv::Mat image) {
    std::vector<cv::Vec3f> circlesFloat;
    cv::HoughCircles(image, circlesFloat, cv::HOUGH_GRADIENT, 1.5, 50, 100, 100, 20);
    std::cout << circlesFloat.size() << " circles found" << std::endl;
    std::vector<cv::Vec3i> circlesInt = vectorOfVec3FloatToInt(circlesFloat);
    cv::Mat tempImage;
    image.copyTo(tempImage);
    // drawHoughCircles(tempImage, circlesInt);
    // popUpImage(tempImage);
    // circlesInt is sorted by highest rating -> circlesInt[0] should be the most prominent circle detected
    _circle.center.x = circlesInt[0][0];
    _circle.center.y = circlesInt[0][1];
    _circle.radius = circlesInt[0][2];
}

cv::Rect Cap::_circleRegionOfInterest(cv::Mat image) {
    int& x = _circle.center.x;
    int& y = _circle.center.y;
    int& r = _circle.radius;
    cv::Rect boundingRect(x-r, y-r, r*2,r*2); 
    return boundingRect;
}

void Cap::_cutOutBottleCap() {
    // Load image
    cv::Mat sourceImage = cv::imread(sourceImagePath.string());
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
    // popUpImage(croppedImage);
    
    // Create circular mask
    _mask = cv::Mat::zeros(croppedImage.rows,croppedImage.cols, CV_8U);
    cv::circle(_mask, cv::Point(_circle.radius,_circle.radius),_circle.radius,cv::Scalar::all(1),-1);
    
    // Apply mask / black out background
    croppedImage.copyTo(_bottleCap,_mask);
    // Save cutout bottle cap
    std::filesystem::path cutOutsName {"cutouts"};
    cutOutImagePath = sourceImagePath.parent_path().parent_path() / cutOutsName / sourceImagePath.filename();
    cv::imwrite(cutOutImagePath.string(),_bottleCap);

    popUpImage(_bottleCap);
}

void Cap::_computeAverageColor() {
    _averageColor = cv::mean(_bottleCap,_mask);
}