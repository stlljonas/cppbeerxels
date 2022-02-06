#include "SmartCircle.h"
#include "helpers.h"
#include "Cerial.h"

int SmartCircle::getRadius() { return _radius; }

cv::Point SmartCircle::getCenterPoint() { return _centerPoint; }

void SmartCircle::detectCircle(cv::Mat rawImage) {

  // Preprocess for circle detection
  cv::Mat workingImage;
  cv::medianBlur(rawImage, workingImage, _blurAperture);
  cv::cvtColor(workingImage, workingImage, cv::COLOR_BGR2GRAY);

  // Detect Circle(s)
  std::vector<cv::Vec3f> circlesFloat;
  cv::HoughCircles(workingImage, circlesFloat, cv::HOUGH_GRADIENT, 1.5, 10, 100,
                   80, 30);
  std::vector<cv::Vec3i> circlesInt = _Vec3i(circlesFloat);
  drawHoughCircles(workingImage,circlesInt);
  Cerial::print<std::size_t>(circlesInt.size(),DEBUG);
  Cerial::println(" circles detected",DEBUG);
  Cerial::showImage(workingImage,DEBUG);
  // circlesInt is sorted by highest rating -> circlesInt[0] should be the most
  // prominent circle detected
  if (!circlesInt.empty()) {
    _centerPoint.x = circlesInt[0][0];
    _centerPoint.y = circlesInt[0][1];
    _radius = circlesInt[0][2];
  } else { // keep radius at 0 but but center in center of image
    _centerPoint.x = rawImage.size[0]/2;
    _centerPoint.y = rawImage.size[1]/2;
  }
}

cv::Mat SmartCircle::cutOutCircle(cv::Mat image) {
  // copy circle onto blank image
  cv::Mat isolatedImage;
  image.copyTo(isolatedImage, computeMask(image));
  // crop to redion of interest (of circle)
  cv::Rect range = regionOfInterest();
  cv::Mat croppedImage = isolatedImage(range);
  return croppedImage;
}

cv::Scalar SmartCircle::computeAverageColor(cv::Mat image) {
  return cv::mean(image, computeMask(image));
}

std::vector<cv::Vec3i>
SmartCircle::_Vec3i(const std::vector<cv::Vec3f> &floatVector) {
  std::vector<cv::Vec3i> intVector;
  for (size_t i = 0; i < floatVector.size(); ++i) {
    intVector.push_back(static_cast<cv::Vec3i>(floatVector[i]));
  }
  return intVector;
}

cv::Mat SmartCircle::computeMask() {
  cv::Rect roi = regionOfInterest();
  cv::Mat mask = cv::Mat::zeros(roi.size(), CV_8U);
  cv::circle(mask, cv::Point(_radius, _radius), _radius, cv::Scalar::all(1),
             -1);
  return mask;
}

cv::Mat SmartCircle::computeMask(cv::Mat image) {
  cv::Mat mask = cv::Mat::zeros(image.size(), CV_8U);
  cv::circle(mask, _centerPoint, _radius, cv::Scalar::all(1), -1);
  return mask;
}

cv::Rect SmartCircle::regionOfInterest() {
  int &x = _centerPoint.x;
  int &y = _centerPoint.y;
  int &r = _radius;
  cv::Rect boundingRect(x - r, y - r, r * 2 + 1, r * 2 + 1);
  return boundingRect;
}

// pass negative or positive integer to specify direction
void SmartCircle::shiftCenterX(int numberOfPixels) {
  // edge case
  if (_centerPoint.x+numberOfPixels <= 0) {
    _centerPoint.x = 0;
  } else {
    _centerPoint.x += numberOfPixels;
  }
}

// pass negative or positive integer to specify direction
void SmartCircle::shiftCenterY(int numberOfPixels) {
  // edge case
  if (_centerPoint.y+numberOfPixels <= 0) {
    _centerPoint.y = 0;
  } else {
    _centerPoint.y += numberOfPixels;
  }
}

// pass negative or positive integer to specify direction
void SmartCircle::varyRadius(int numberOfPixels) {
  // edge case
  if (_radius+numberOfPixels <= 0) {
    _radius = 0;
  } else {
    _radius += numberOfPixels;
  }
}