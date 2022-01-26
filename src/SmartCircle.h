#ifndef _SMART_CIRCLE_H_
#define _SMART_CIRCLE_H_

#include <opencv2/opencv.hpp>

class SmartCircle {
public:
  SmartCircle(){};
  SmartCircle(cv::Point center, int radius)
      : _centerPoint(center), _radius(radius){};
  int getRadius();
  cv::Point getCenterPoint();
  void detectCircle(cv::Mat image);
  cv::Mat cutOutCircle(cv::Mat image);
  cv::Scalar computeAverageColor(cv::Mat image);
  cv::Rect regionOfInterest();
  cv::Mat computeMask();
  cv::Mat computeMask(cv::Mat image);

private:
  int _radius;
  // x equals width, left to right, equals cols
  // y equals height, top to bottom, equals rows
  cv::Point _centerPoint;
  int _blurAperture = 7;
  std::vector<cv::Vec3i> _Vec3i(const std::vector<cv::Vec3f> &floatVector);
};

#endif /* _SMART_CIRCLE_H_ */