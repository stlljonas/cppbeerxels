#ifndef _CAP_H_
#define _CAP_H_

#include<string>
#include<opencv2/opencv.hpp>

class Cap {
  public:	
	std::string sourceImagePath;
	std::string cutOutImagePath;
	cv::Mat sourceImage;
	cv::Scalar averageColor; // is this the righty datatype?
	// Cuts out image from sourceImagePath and saves it at cutOutImagePath;
	cv::Mat getBottleCap();
  private:
	bool capHasBeenCutOut = false;
	cv::Mat cutOutBottleCap();
	cv::Mat BottleCap;
	int aperture = 3;
	// circle size
	// circle position
};

#endif /* _CAP_H_ */