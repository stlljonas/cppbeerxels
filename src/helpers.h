#ifndef _HELPERS_H_
#define _HELPERS_H_

#include<opencv2/opencv.hpp>

void popUpImage(cv::Mat image);

void drawHoughCircles(cv::Mat image, std::vector<cv::Vec3i> circles);

std::vector<cv::Vec3i> vectorOfVec3FloatToInt(const std::vector<cv::Vec3f>& floatVector);
//todo
// rename all files in data squentially 
void rawDataSequentialRename();
// delete all non rawdata images
void purgeData();

#endif /* _HELPERS_H_ */