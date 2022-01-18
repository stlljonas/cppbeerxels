# include "helpers.h"

void popUpImage(cv::Mat image) {
    cv::imshow("image",image);
    cv::waitKey(0);
    cv::destroyWindow("image");
};

void drawHoughCircles(cv::Mat image, std::vector<cv::Vec3i> circles) {
    for (int i = circles.size()-1; i >= 0; --i) {
        if (i == 0) cv::circle(image,cv::Point(circles[i][0], circles[i][1]), circles[i][2], cv::Scalar(255, 255, 225));
        else cv::circle(image,cv::Point(circles[i][0], circles[i][1]), circles[i][2], cv::Scalar(0, 0, 255));
    }
};

std::vector<cv::Vec3i> vectorOfVec3FloatToInt(const std::vector<cv::Vec3f>& floatVector) {
    std::vector<cv::Vec3i> intVector;
    for (size_t i = 0; i < floatVector.size(); ++i) {
        intVector.push_back(static_cast<cv::Vec3i>(floatVector[i]));
    }
    return intVector;
}
