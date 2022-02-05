#include "Cap.h"
#include "Cerial.h"

enum ubuntuKeyCodes {
  a = 1048673,
  b = 1048674,
  c = 1048675,
  d = 1048676,
  e = 1048677,
  f = 1048678,
  g = 1048679,
  h = 1048680,
  i = 1048681,
  j = 1048682,
  k = 1048683,
  l = 1048684,
  m = 1048685,
  n = 1048686,
  o = 1048687,
  p = 1048688,
  q = 1048689,
  r = 1048690,
  s = 1048691,
  t = 0,
  u = 1048693,
  v = 1048694,
  w = 1048695,
  x = 1048696,
  y = 1048697,
  z = 1048698,
  ENTER = 1048589,
  ARROWLEFT = 1113937,
  ARROWUP = 1113938,
  ARROWRIGHT = 1113939,
  ARROWDOWN = 1113940
};

void Cap::analyze(bool tuning) {
  
  Cerial::print("Analyzing image ",VERBOSE);
  Cerial::println(_sourceImagePath.filename().string(),VERBOSE);
  
  cv::Mat image = cv::imread(_sourceImagePath.string());
  image = _uniformRescale(image);
  _circle.detectCircle(image);

  if (tuning) _tuneCircle(image);

  Cerial::print("Deected circle radius = ",DEBUG);
  Cerial::println<int>(_circle.getRadius(),DEBUG);
  if (_circle.getRadius() > 1) {
    _validity = true;
  } else {
    Cerial::print(_sourceImagePath.string(),VERBOSE);
    Cerial::println(" is invalid!", VERBOSE);
  }
  _bottleCap = _circle.cutOutCircle(image);
  _averageColor = _circle.computeAverageColor(/*_bottleCap*/ image);
  //_bottleCap = _cutOutBottleCap(image);
  Cerial::showImage(_bottleCap, NORMAL,100);
  _saveBottleCap(_bottleCap);
}

cv::Mat Cap::getBottleCap() const { return _bottleCap; }

cv::Scalar Cap::getAverageColor() const { return _averageColor; }

bool Cap::isValid() {
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

void Cap::_tuneCircle(cv::Mat image) {
  cv::imshow("tuning", image);
  std::cout << "Starting tuning process\n";
  std::cout << "Press 'c' at any time to see list of command options\n";
  bool finished = false;
  while (!finished) {
    // show image with circle
    cv::Mat circleImage = image.clone();
    cv::circle(circleImage, _circle.getCenterPoint(), _circle.getRadius(), cv::Scalar(0,255,0));
    cv::imshow("tuning", circleImage);
    int currentKey = cv::waitKeyEx();
    switch(currentKey) {
      case c: {
        std::cout << "[ENTER]: confirm circle\n"
                  << "[q]: discard bottleCap\n"
                  << "[w]: increase radius\n"
                  << "[s]: decrease radius\n"
                  << "[ARROWLEFT]: shift center left\n"
                  << "[ARROWUP]: shift center up\n"
                  << "[ARROWRIGHT]: shift center right\n"
                  << "[ARROWDOWN]: shift center down\n";
        break;
      }
      case ENTER: {
        _validity = true;
        finished = true;
        break;
      }
      case q: {
        _validity = false;
        finished = true;
        break;
      }
      case w: {
        _circle.varyRadius(1);
        break;
      }
      case s: {
        _circle.varyRadius(-1);
        break;
      }
      case ARROWLEFT: {
        _circle.shiftCenterX(-1);
        break;
      }
      case ARROWUP: {
        _circle.shiftCenterY(-1);
        break;
      }
      case ARROWRIGHT: {
        _circle.shiftCenterX(1);
        break;
      }
      case ARROWDOWN: {
        _circle.shiftCenterY(1);
        break;
      }
      default:
        std::cout << "INVALID COMMAND\n";
        break;
    }
  }
  cv::destroyWindow("tuning");
}

void Cap::_autoTuneCircle() {

}