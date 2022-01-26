#include "helpers.h"

void popUpImage(cv::Mat image) {
  cv::imshow("image", image);
  cv::waitKey(0);
  cv::destroyWindow("image");
};

void drawHoughCircles(cv::Mat image, std::vector<cv::Vec3i> circles) {
  for (int i = circles.size() - 1; i >= 0; --i) {
    if (i == 0)
      cv::circle(image, cv::Point(circles[i][0], circles[i][1]), circles[i][2],
                 cv::Scalar(255, 255, 225));
    else
      cv::circle(image, cv::Point(circles[i][0], circles[i][1]), circles[i][2],
                 cv::Scalar(0, 0, 255));
  }
};

std::vector<cv::Vec3i>
vectorOfVec3FloatToInt(const std::vector<cv::Vec3f> &floatVector) {
  std::vector<cv::Vec3i> intVector;
  for (size_t i = 0; i < floatVector.size(); ++i) {
    intVector.push_back(static_cast<cv::Vec3i>(floatVector[i]));
  }
  return intVector;
}

std::string type2str(int type) {
  std::string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

void resizeImage(std::filesystem::path imageFilePath, std::filesystem::path destinationPath, double factor) {
  cv::Mat image = cv::imread(imageFilePath.string());
  cv::resize(image,image,cv::Size(),factor,factor);
  cv::imwrite(destinationPath.string(), image);
}

