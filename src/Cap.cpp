#include "Cap.h"
#include "Cerial.h"

void Cap::analyze() {
  cv::Mat image = cv::imread(_sourceImagePath.string());
  image = _uniformRescale(image);
  _circle.detectCircle(image);
  _bottleCap = _circle.cutOutCircle(image);
  _averageColor = _circle.computeAverageColor(/*_bottleCap*/ image);
  //_bottleCap = _cutOutBottleCap(image);
  Cerial::showImage(_bottleCap, NORMAL,100);
  _saveBottleCap(_bottleCap);
}

cv::Mat Cap::getBottleCap() const { return _bottleCap; }

cv::Scalar Cap::getAverageColor() const { return _averageColor; }

uint Cap::_imageMaxDimension = 500;

cv::Mat Cap::_uniformRescale(cv::Mat image) {
  int largerDimensionSize;
  if (image.size[0] >= image.size[1]) {
    largerDimensionSize = image.size[0];
  } else {
    largerDimensionSize = image.size[1];
  }
  double scaling = static_cast<double>(_imageMaxDimension) /
    static_cast<double>(largerDimensionSize);
  cv::resize(image, image, cv::Size(), scaling, scaling);
  return image;    
}

void Cap::_saveBottleCap(cv::Mat bottleCap) {
  std::filesystem::path cutOutsName{"cutouts"};
  std::filesystem::path cutOutImagePath =
      _sourceImagePath.parent_path().parent_path() / cutOutsName /
      _sourceImagePath.filename();
  cv::imwrite(cutOutImagePath.string(), bottleCap);
  // possibly change permissions using std::filesystem
};
