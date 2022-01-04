#ifndef _CAP_H_
#define _CAP_H_

#include<string>
#include<opencv2/opencv.hpp>
#include"Circle.h"
#include"helpers.h"

class Cap {
  public:	
	std::string sourceImagePath;
	std::string cutOutImagePath;
	cv::Mat sourceImage;
	// Cuts out image from sourceImagePath and saves it at cutOutImagePath;
	cv::Mat getBottleCap();
	// cv::Scalar getAverageColor();
	Cap() = default; 
	Cap(const int blurAperture_, const int logLevel_ = 0) : blurAperture(blurAperture_), logLevel(logLevel_){};
	// void showCircle();
  private:
	Circle circle;
  	void _detectCircle(cv::Mat image);
	cv::Rect _circleRegionOfInterest(cv::Mat image);
	cv::Mat BottleCap;
	void _cutOutBottleCap();
	int blurAperture = 1;
	// 0 = none, 1 = text, 2 = text & images
	int logLevel = 0;
	cv::Scalar averageColor;
};

#endif /* _CAP_H_ */