#include "Cap.h"

void Cap::analyze() {
  cv::Mat image = cv::imread(_sourceImagePath.string());
  _circle.detectCircle(image);
  _bottleCap = _circle.cutOutCircle(image);
  _averageColor = _circle.computeAverageColor(/*_bottleCap*/ image);
  //_bottleCap = _cutOutBottleCap(image);
  popUpImage(_bottleCap);
  _saveBottleCap(_bottleCap);
}

cv::Mat Cap::getBottleCap() const { return _bottleCap; }

cv::Scalar Cap::getAverageColor() const { return _averageColor; }

/*cv::Mat Cap::_cutOutBottleCap(cv::Mat image) {
  // Detect Circle
  _circle.detectCircle(image);
  // Cut out bottle cap
  return _circle.cutOutCircle(image);
}*/

void Cap::_saveBottleCap(cv::Mat bottleCap) {
  std::filesystem::path cutOutsName{"cutouts"};
  std::filesystem::path cutOutImagePath =
      _sourceImagePath.parent_path().parent_path() / cutOutsName /
      _sourceImagePath.filename();
  cv::imwrite(cutOutImagePath.string(), bottleCap);
  // possibly change permissions using std::filesystem
};