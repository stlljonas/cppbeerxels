#include "Cap.h"

void Cap::analyze() {
    _cutOutBottleCap();
    std::cout << "check\n";
    _computeAverageColor();
    // still need to save computation
}

cv::Mat Cap::getBottleCap() const {
    return _bottleCap;
}

cv::Scalar Cap::getAverageColor() const {
    return _averageColor;
}

void Cap::_cutOutBottleCap() {
    
    // Load image
    cv::Mat image = cv::imread(sourceImagePath.string());

    // Detect Circle 
    _circle.detectCircle(image);
    
    // Cut out circle
    cv::Mat _bottleCap = _circle.cutOutCircle(image);
    // Save cut out bottle cap
    std::filesystem::path cutOutsName {"cutouts"};
    cutOutImagePath = sourceImagePath.parent_path().parent_path() / cutOutsName / sourceImagePath.filename();
    cv::imwrite(cutOutImagePath.string(),_bottleCap);

    // Show cut out bottle
    popUpImage(_bottleCap);
}

void Cap::_computeAverageColor() {
    _averageColor = cv::mean(_bottleCap,_mask);
}