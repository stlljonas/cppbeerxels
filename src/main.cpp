#include "CapShepherd.h"
#include "helpers.h"
#include "CapField.h"

int main(){
    /*Cap cap(7);
    cap.sourceImagePath = "/home/jstolle/code/cppbeerxels/data/raw/bottle-cap-2.jpg";
    cap.analyze();
    cv::Mat bottleCapCutOut = cap.getBottleCap();
    cv::Mat averageColor(300,300, CV_8UC3, cap.getAverageColor());
    popUpImage(averageColor);
    */
    std::string rawImgDirPath = "/home/jstolle/code/cppbeerxels/data/raw/";
    // CapShepherd shepherd(rawImgDirPath);
    // shepherd.init();
    HoneyCombTiling tiling(400,500,25);
    tiling.optimalTiling();
    //tiling.showNodes();
}