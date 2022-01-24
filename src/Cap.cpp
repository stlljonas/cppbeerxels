#include "Cap.h"

void Cap::analyze() {
  cv::Mat image = cv::imread(_sourceImagePath.string());
  std::cout << "cutoutbottlecap\n";
  _bottleCap = _cutOutBottleCap(image);
  std::cout << "saveBottlecap\n";
  _saveBottleCap();
  std::cout << "computeAverage color\n";
  _averageColor = _circle.computeAverageColor(_bottleCap);
  std::cout << "after\n";
  // still need to save computation
}

cv::Mat Cap::getBottleCap() const { return _bottleCap; }

cv::Scalar Cap::getAverageColor() const { return _averageColor; }

cv::Mat Cap::_cutOutBottleCap(cv::Mat image) {
  // Detect Circle
  _circle.detectCircle(image);
  // Cut out bottle cap
  return _circle.cutOutCircle(image);
}

void Cap::_saveBottleCap() {
  std::filesystem::path cutOutsName{"cutouts"};
  std::filesystem::path cutOutImagePath = _sourceImagePath.parent_path().parent_path() / cutOutsName /
                    _sourceImagePath.filename();
  cv::imwrite(cutOutImagePath.string(), _bottleCap);
  // possibly change permissions using std::filesystem
};