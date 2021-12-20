#include "Cap.h"

cv::Mat Cap::cutOutBottleCap() {
    cv::Mat image = cv::imread(sourceImagePath);
    // run circle detection algorithm
    cv::Mat blurredImage;
    cv::medianBlur(image,blurredImage,aperture);
    image.
    return image;
};

cv::Mat Cap::getBottleCap() {
    if (capHasBeenCutOut) {
        return BottleCap;
    }
    // try to load it from file
    // call cutOutBottleCap()
}