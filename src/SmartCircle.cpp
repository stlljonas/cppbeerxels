#include "SmartCircle.h"
#include "Cerial.h"

enum UbuntuKeyCodes {
  a = 1048673,
  b = 1048674,
  c = 1048675,
  d = 1048676,
  e = 1048677,
  f = 1048678,
  g = 1048679,
  h = 1048680,
  i = 1048681,
  j = 1048682,
  k = 1048683,
  l = 1048684,
  m = 1048685,
  n = 1048686,
  o = 1048687,
  p = 1048688,
  q = 1048689,
  r = 1048690,
  s = 1048691,
  t = 0,
  u = 1048693,
  v = 1048694,
  w = 1048695,
  x = 1048696,
  y = 1048697,
  z = 1048698,
  ENTER = 1048589,
  ARROWLEFT = 1113937,
  ARROWUP = 1113938,
  ARROWRIGHT = 1113939,
  ARROWDOWN = 1113940
};
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
  _drawHoughCircles(workingImage,circlesInt);
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

void SmartCircle::_drawHoughCircles(cv::Mat image, std::vector<cv::Vec3i> circles) {
  for (int i = circles.size() - 1; i >= 0; --i) {
    if (i == 0)
      cv::circle(image, cv::Point(circles[i][0], circles[i][1]), circles[i][2],
                 cv::Scalar(255, 255, 225));
    else
      cv::circle(image, cv::Point(circles[i][0], circles[i][1]), circles[i][2],
                 cv::Scalar(0, 0, 255));
  }
};

// pass negative or positive integer to specify direction
void SmartCircle::_shiftCenterX(int numberOfPixels) {
  // edge case
  if (_centerPoint.x+numberOfPixels <= 0) {
    _centerPoint.x = 0;
  } else {
    _centerPoint.x += numberOfPixels;
  }
}

// pass negative or positive integer to specify direction
void SmartCircle::_shiftCenterY(int numberOfPixels) {
  // edge case
  if (_centerPoint.y+numberOfPixels <= 0) {
    _centerPoint.y = 0;
  } else {
    _centerPoint.y += numberOfPixels;
  }
}

// pass negative or positive integer to specify direction
void SmartCircle::_varyRadius(int numberOfPixels) {
  // edge case
  if (_radius+numberOfPixels <= 0) {
    _radius = 0;
  } else {
    _radius += numberOfPixels;
  }
}

ReturnAction SmartCircle::tuneCircle(cv::Mat image) {
  cv::imshow("tuning", image);
  bool finished = false;
  ReturnAction returnAction;
  while (!finished) {
    // show image with circle
    cv::Mat circleImage = image.clone();
    cv::circle(circleImage, _centerPoint, _radius, cv::Scalar(0,255,0));
    cv::imshow("tuning", circleImage);
    int currentKey = cv::waitKeyEx();
    switch(currentKey) {
      case c: {
        std::cout << "[ENTER]: confirm circle\n"
                  << "[q]: discard circle\n"
                  << "[r]: go back to previous image\n"
                  << "[w]: increase radius\n"
                  << "[s]: decrease radius\n"
                  << "[ARROWLEFT]: shift center left\n"
                  << "[ARROWUP]: shift center up\n"
                  << "[ARROWRIGHT]: shift center right\n"
                  << "[ARROWDOWN]: shift center down\n";
        break;
      }
      case ENTER: {
        returnAction = ACCEPT_CIRCLE;
        finished = true;
        break;
      }
      case q: {
        returnAction = REJECT_CIRCLE;
        finished = true;
        break;
      }
      case r: {
        returnAction = RETUNE_PREVIOUS;
        finished = true;
        break;
      }
      case w: {
        _varyRadius(1);
        break;
      }
      case s: {
        _varyRadius(-1);
        break;
      }
      case ARROWLEFT: {
        _shiftCenterX(-1);
        break;
      }
      case ARROWUP: {
        _shiftCenterY(-1);
        break;
      }
      case ARROWRIGHT: {
        _shiftCenterX(1);
        break;
      }
      case ARROWDOWN: {
        _shiftCenterY(1);
        break;
      }
      default:
        std::cout << "INVALID COMMAND\n";
        break;
    }
  }
  cv::destroyWindow("tuning");
  return returnAction;
}