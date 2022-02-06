#ifndef _SMART_CIRCLE_H_
#define _SMART_CIRCLE_H_

#include <opencv2/opencv.hpp>

enum ReturnAction {
  REJECT_CIRCLE = 0,
  ACCEPT_CIRCLE = 1,
  RETUNE_PREVIOUS = 2 // this doesn't quite follow the single responsibility principle..
};

class SmartCircle {
public:
  SmartCircle(){};
  SmartCircle(cv::Point center, int radius)
      : _centerPoint(center), _radius(radius){};
  int getRadius();
  cv::Point getCenterPoint();
  void detectCircle(cv::Mat image);
  ReturnAction tuneCircle(cv::Mat image);
  cv::Mat cutOutCircle(cv::Mat image);
  cv::Scalar computeAverageColor(cv::Mat image);
  cv::Rect regionOfInterest();
  cv::Mat computeMask();
  cv::Mat computeMask(cv::Mat image);

private:
  void _shiftCenterX(int numberOfPixels);
  void _shiftCenterY(int numberOfPixels);
  void _varyRadius(int numberOfPixels);
  std::vector<cv::Vec3i> _Vec3i(const std::vector<cv::Vec3f> &floatVector);
  
  int _radius = 0;
  // x equals width, left to right, equals cols index
  // y equals height, top to bottom, equals rows index
  cv::Point _centerPoint;
  int _blurAperture = 7;
};

#endif /* _SMART_CIRCLE_H_ */