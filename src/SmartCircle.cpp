#include "SmartCircle.h"

int SmartCircle::getRadius() { return _radius; }

cv::Point SmartCircle::getCenterPoint() { return _centerPoint; }

void SmartCircle::detectCircle(cv::Mat rawImage) {

  // Preprocess for circle detection
  cv::Mat workingImage;
  cv::medianBlur(rawImage, workingImage, _blurAperture);
  cv::cvtColor(workingImage, workingImage, cv::COLOR_BGR2GRAY);

  // Detect Circle(s)
  std::vector<cv::Vec3f> circlesFloat;
  cv::HoughCircles(workingImage, circlesFloat, cv::HOUGH_GRADIENT, 1.5, 50, 100,
                   100, 20);
  std::vector<cv::Vec3i> circlesInt = _Vec3i(circlesFloat);

  // circlesInt is sorted by highest rating -> circlesInt[0] should be the most
  // prominent circle detected
  _centerPoint.x = circlesInt[0][0];
  _centerPoint.y = circlesInt[0][1];
  _radius = circlesInt[0][2];
  std::cout << "radius = " << _radius << std::endl;
  std::cout << "centerpoint = " << _centerPoint.x << ", " << _centerPoint.y << std::endl;
}

cv::Mat SmartCircle::cutOutCircle(cv::Mat image) {
  cv::Rect range = _regionOfInterest();
  cv::Mat croppedImage = image(range);
  cv::Mat result;
  croppedImage.copyTo(result, _computeMask());
  return result;
}

cv::Scalar SmartCircle::computeAverageColor(cv::Mat image) {
  // cv::Mat cutoutImage = cutOutCircle(image);
  return cv::mean(image, _computeMask());
}

std::vector<cv::Vec3i>
SmartCircle::_Vec3i(const std::vector<cv::Vec3f> &floatVector) {
  std::vector<cv::Vec3i> intVector;
  for (size_t i = 0; i < floatVector.size(); ++i) {
    intVector.push_back(static_cast<cv::Vec3i>(floatVector[i]));
  }
  return intVector;
}

cv::Mat SmartCircle::_computeMask() {
  cv::Rect roi = _regionOfInterest();
  cv::Mat mask = cv::Mat::zeros(roi.size(), CV_8U);
  cv::circle(mask, cv::Point(_radius, _radius), _radius, cv::Scalar::all(1),
             -1);
  return mask;
}

cv::Rect SmartCircle::_regionOfInterest() {
  int &x = _centerPoint.x;
  int &y = _centerPoint.y;
  int &r = _radius;
  cv::Rect boundingRect(x - r, y - r, r * 2, r * 2);
  //std::cout << "boundigrect size = " << boundingRect.size() << std::endl;
  return boundingRect;
}