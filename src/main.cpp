#include "Cap.h"

int main(){
    Cap cap;
    cap.sourceImagePath = "/home/jstolle/code/cppbeerxels/data/bottle-cap.jpg";
    // cv::Mat image = cv::imread("../data/bottle-cap.jpg");
    //cv::imshow("Bottle-cap", image);
    cv::Mat image = cap.cutOutBottleCap();
    cv::imshow("image",image);
    cv::waitKey(0);
    cv::destroyWindow("image");
}