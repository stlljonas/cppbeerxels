#include "Tiling.h"
#include <math.h>
#include "Cerial.h"

void HoneyCombTiling::optimalTiling() {
  Cerial::println("Computing optimal tiling");
  
  // find optimal radius
  _radius = 1;
  while (_findNumberOfNodes(_radius) > _maxNumberOfNodes) {
    Cerial::indicateProgress();
    ++_radius;
    Cerial::print("Current radius = ", DEBUG);
    Cerial::println(_radius, DEBUG);
    
    _nodes = _tile(_radius);
    
    _centerNodes();
    Cerial::showImage(drawNodes(), VERBOSE, 20);
  };
  Cerial::endProgress();
  Cerial::print("Optimal nodes number = ", VERBOSE);
  Cerial::println<std::size_t>(_nodes.size(), VERBOSE);
  Cerial::print("Optimal radius = ", VERBOSE);
  Cerial::println<std::size_t>(_radius, VERBOSE);

  Cerial::showImage(drawNodes(),NORMAL, 500);
}

std::vector<cv::Point> HoneyCombTiling::getNodes() { return _nodes; }

int HoneyCombTiling::getRadius() { return _radius; }

void HoneyCombTiling::setDimensions(const int xDimension,
                                    const int yDimension) {
  _referenceXDimension = xDimension;
  _referenceYDimension = yDimension;
}

void HoneyCombTiling::setMaxNumNodes(const int maxNumNodes) {
  _maxNumberOfNodes = maxNumNodes;
}

std::vector<cv::Point> HoneyCombTiling::_tile(int radius) {
  std::vector<cv::Point> nodes;
  float xCurr = static_cast<float>(radius); // x value of current node
  float yCurr = static_cast<float>(radius); // y value of current node
  bool indentedRow = false;
  const float xStep =
      2.0 * static_cast<float>(radius); // step size in x direction
  // cos(30) = h/(2r) = sqrt(3)/2
  // h = sqrt(3)*r
  const float yStep =
      sqrt(3) * static_cast<float>(radius); // step size in y direction

  while (_circleIsInBound(xCurr, yCurr, radius)) {   // iterate over y
    while (_circleIsInBound(xCurr, yCurr, radius)) { // iterate over x
      cv::Point node(_nearestInt(xCurr), _nearestInt(yCurr));
      nodes.push_back(node);
      xCurr += xStep; // shift x coorsdinate
    }
    if (indentedRow) { // reset x coordinate
      xCurr = static_cast<float>(radius);
      indentedRow = false;
    } else {
      xCurr = 2 * static_cast<float>(radius);
      indentedRow = true;
    }
    yCurr += yStep; // shift y coordinate
  }
  return nodes;
}

size_t HoneyCombTiling::_findNumberOfNodes(int radius) {
  return _tile(radius).size();
}

bool HoneyCombTiling::_circleIsInBound(int x, int y, int radius) {
  if (x - radius < 0 || y - radius < 0) {
    return false;
  } else if (x + radius >= _referenceXDimension ||
             y + radius >= _referenceYDimension) {
    return false;
  } else {
    return true;
  }
}

bool HoneyCombTiling::_circleIsInBound(float xFloat, float yFloat, int radius) {
  int x = _nearestInt(xFloat);
  int y = _nearestInt(yFloat);
  if (x - radius < 0 || y - radius < 0) {
    return false;
  } else if (x + radius >= _referenceXDimension ||
             y + radius >= _referenceYDimension) {
    return false;
  } else {
    return true;
  }
}

cv::Mat HoneyCombTiling::drawNodes() {
  cv::Mat canvas = cv::Mat::zeros(
      cv::Size(_referenceXDimension, _referenceYDimension), CV_8UC1);
  for (auto entry : _nodes) {
    cv::circle(canvas, entry, _radius, cv::Scalar(255, 255, 225));
  }
  return canvas;
}

cv::Mat HoneyCombTiling::drawNodes(std::vector<cv::Point> nodes, int radius) {
  cv::Mat canvas = cv::Mat::zeros(
      cv::Size(_referenceXDimension, _referenceYDimension), CV_8UC1);
  for (auto entry : nodes) {
    cv::circle(canvas, entry, radius, cv::Scalar(255, 255, 225));
  }
  return canvas;
}

int HoneyCombTiling::_nearestInt(float f) {
  // might cause issues with very large floats according to SO
  return static_cast<int>(f >= 0 ? f + 0.5 : f - 0.5);
}

void HoneyCombTiling::_centerNodes() {
  // find offsets
  int xmax = 0;
  int ymax = 0;
  for (auto entry : _nodes) {
    if (entry.x > xmax)
      xmax = entry.x;
    if (entry.y > ymax)
      ymax = entry.y;
  }
  int xOffset = (_referenceXDimension - (xmax + _radius)) / 2;
  int yOffset = (_referenceYDimension - (ymax + _radius)) / 2;
  // apply offset
  for (auto &entry : _nodes) {
    entry.x += xOffset;
    entry.y += yOffset;
  }
}
