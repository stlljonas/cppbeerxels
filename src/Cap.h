#ifndef _CAP_H_
#define _CAP_H_

#include<string>
#include<opencv2/opencv.hpp>
#include<filesystem>
#include"Circle.h"
#include"helpers.h"
#include "SmartCircle.h"

class Cap {
  public:	
	std::filesystem::path sourceImagePath;
	std::filesystem::path cutOutImagePath;
	cv::Mat sourceImage;
	// Cuts out image from sourceImagePath and saves it at cutOutImagePath;
	void analyze(); // calls all the private methods
	cv::Mat getBottleCap() const;
	cv::Scalar getAverageColor() const;
	Cap() = default; 
	Cap(std::filesystem::path sourceImagePath_ , const int blurAperture_ = 7, const int logLevel_ = 0) : sourceImagePath(sourceImagePath_), blurAperture(blurAperture_), logLevel(logLevel_){};
	// void showCircle();
  private:
	SmartCircle _circle;
	cv::Mat _bottleCap;
	cv::Mat _mask;
	cv::Scalar _averageColor;
	void _cutOutBottleCap();
	void _computeAverageColor();
	int blurAperture = 7;
	// 0 = none, 1 = text, 2 = text & images
	int logLevel = 0;
	
};

#endif /* _CAP_H_ */