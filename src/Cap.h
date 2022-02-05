#ifndef _CAP_H_
#define _CAP_H_

#include "Circle.h"
#include "SmartCircle.h"
#include "helpers.h"
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <string>

class Cap {
public:
  Cap() = default;
  Cap(std::filesystem::path sourceImagePath_/*,
      const int logLevel_ = 0*/)
      : _sourceImagePath(sourceImagePath_)/*,
        logLevel(logLevel_)*/{};

  void analyze(bool tuning = false); // add tuning choice as parameter
  cv::Mat getBottleCap() const;
  cv::Scalar getAverageColor() const;
  bool isValid();

private:
  SmartCircle _circle;
  cv::Mat _bottleCap;
  cv::Mat _mask;
  cv::Scalar _averageColor;
  std::filesystem::path _sourceImagePath;
  static uint _imageMaxDimension;
  bool _validity = false;
  cv::Mat _uniformRescale(cv::Mat image);
  void _saveBottleCap(cv::Mat bottleCap);
  void _tuneCircle(cv::Mat image); // move back to private
  void _autoTuneCircle();
};

#endif /* _CAP_H_ */