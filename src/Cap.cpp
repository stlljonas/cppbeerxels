#include "Cap.h"

cv::Mat Cap::cutOutBottleCap() {
    cv::Mat image = cv::imread(sourceImagePath);
    // run circle detection algorithm
    cv::Mat blurredImage;
    cv::medianBlur(image,blurredImage,aperture);

    cv::cvtColor(image,image,6);
    return image;
};

cv::Mat Cap::getBottleCap() {
    if (capHasBeenCutOut) {
        return BottleCap;
    }
    return BottleCap; // temp   
    // try to load it from file
    // call cutOutBottleCap()
    // save cutout to file
    // cv::imwrite()
}