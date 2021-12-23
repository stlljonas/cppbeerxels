#include "Cap.h"

int main(){
    Cap cap;
    cv::Mat image = cv::imread("../data/bottle-cap.jpg");
    cv::imshow("Bottle-cap", image);
    cv::waitKey(0);
    cv::destroyWindow("Bottle-cap");
}