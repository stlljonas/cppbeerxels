#include "Cap.h"
#include "Cerial.h"

void Cap::init() {
  Cerial::print("Initializing cap ",VERBOSE);
  Cerial::println(_sourceImagePath.filename().string(),VERBOSE);
  
  cv::Mat image = cv::imread(_sourceImagePath.string());
  _workingImage = _uniformRescale(image);
  _circle.detectCircle(_workingImage);

  Cerial::print("Detected circle radius = ",DEBUG);
  Cerial::println<int>(_circle.getRadius(),DEBUG);
  
  if (_circle.getRadius() > 1) {
    _validity = true;
  } else {
    Cerial::print(_sourceImagePath.string(),VERBOSE);
    Cerial::println(" is invalid!", VERBOSE);
  }
  
}

ReturnAction Cap::tune() {
  ReturnAction returnAction = _circle.tuneCircle(_workingImage);
  if (returnAction == ACCEPT_CIRCLE) { 
    _validity = true;
  } else {
    _validity = false;
  }
  return returnAction;
}

void Cap::process() {
  _bottleCap = _circle.cutOutCircle(_workingImage);
  _averageColor = _circle.computeAverageColor(/*_bottleCap*/ _workingImage);
  Cerial::showImage(_bottleCap, NORMAL,100);
  _saveBottleCap(_bottleCap);
}


cv::Mat Cap::getBottleCap() const { return _bottleCap; }

cv::Scalar Cap::getAverageColor() const { return _averageColor; }

bool Cap::isValid() const {
  return _validity;
}

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