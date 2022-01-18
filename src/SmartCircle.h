#ifndef _SMART_CIRCLE_H_
#define _SMART_CIRCLE_H_

#include<opencv2/opencv.hpp>

class SmartCircle {
  public:
    SmartCircle(){};
    int getRadius();
    cv::Point getCenterPoint();
    void detectCircle(cv::Mat image);
    cv::Mat cutOutCircle(cv::Mat image);
  private:
    int _radius;
    cv::Point _centerPoint;

    int _blurAperture = 7;
    std::vector<cv::Vec3i> _Vec3i(const std::vector<cv::Vec3f>& floatVector);
  	cv::Rect _regionOfInterest();
};

#endif /* _SMART_CIRCLE_H_ */