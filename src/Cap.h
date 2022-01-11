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
	void analyze(); // calls all the private methods
	cv::Mat getBottleCap() const;
	cv::Scalar getAverageColor() const;
	Cap() = default; 
	Cap(std::string sourceImagePath_ , const int blurAperture_ = 7, const int logLevel_ = 0) : sourceImagePath(sourceImagePath_), blurAperture(blurAperture_), logLevel(logLevel_){};
	// void showCircle();
  private:
	cv::Mat _bottleCap;
	Circle _circle;
	cv::Mat _mask;
	cv::Scalar _averageColor;
  	void _detectCircle(cv::Mat image);
	cv::Rect _circleRegionOfInterest(cv::Mat image);
	void _cutOutBottleCap();
	void _computeAverageColor();
	int blurAperture = 7;
	// 0 = none, 1 = text, 2 = text & images
	int logLevel = 0;
	
};

#endif /* _CAP_H_ */