#include "Tiling.h"
#include <math.h>
#include "Cerial.h"

void HoneyCombTiling::optimalTiling() {
  Cerial::println("Computing optimal tiling");
  // find optimal radius
  // std::cout << "tiling" << std::endl;
  // int radius = 1;
  _radius = 1;
  // size_t n = _findNumberOfNodes(radius);
  // std::cout << "number of nodes = " << n << std::endl << std::endl;
  // int a;
  // std::cin >> a;
  while (_findNumberOfNodes(_radius) > _maxNumberOfNodes) {
    Cerial::indicateProgress();
    ++_radius;
    // std::cout << "current radius: " << _radius << std::endl;
    Cerial::print("Current radius = ", DEBUG);
    Cerial::println(_radius, DEBUG);
    
    _nodes = _tile(_radius);
    
    _centerNodes();
    Cerial::showImage(drawNodes(), VERBOSE, 20);
  };
  Cerial::endProgress();
  //_radius = radius;
  //std::cout << "optimal radius = " << _radius << std::endl;
  Cerial::print("Optimal nodes number = ", VERBOSE);
  Cerial::println<std::size_t>(_nodes.size(), VERBOSE);
  Cerial::print("Optimal radius = ", VERBOSE);
  Cerial::println<std::size_t>(_radius, VERBOSE);
  // tile with optimal radius
  //_nodes = _tile(_radius);
  // std::cout << "first node = " << _nodes[0].x << ", " << _nodes[0].y <<
  // std::endl; showNodes();
  // std::cout << "first node = " << _nodes[0].x << ", " << _nodes[0].y <<
  // std::endl;
  Cerial::showImage(drawNodes(),NORMAL, 500);
  /*
  // tabula rasa
  _nodes.clear();
  // compute node positions
  float xBorder = _overhangX/2.0;
  float yBorder = _overhangY/2.0;
  for (int j = 0; j < _numberOfNodesY; ++j) { // iterate over y direction
      for (int i = 0; i < _numberOfNodesX; ++i) {
          if (j%2 == 0) { // even row, starting at idx 0
              std::cout << "even" << std::endl;
              // x=
              // y=
              cv::Point point(xBorder
  + 2.0*static_cast<float>(i*_radius),yBorder +
  sqrt(3)*static_cast<float>(j*_radius)); _nodes.push_back(point); } else if
  (!(_everySecondRowOneNodeLess && i == _numberOfNodesX - 1)) { // odd row and
  no edge case std::cout << "odd" << std::endl; cv::Point point(xBorder +
  (2*i+1)*_radius,yBorder + sqrt(3)*j*_radius); _nodes.push_back(point);
          }
          if (_everySecondRowOneNodeLess && j%2 == 1 && i == _numberOfNodesX -
  1) continue;

      }
  } */
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
  // std::cout << "tile\n";
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

  // std::cout << "x,y steps: " << xStep << ", " << yStep << std::endl;

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
    // std::cout << ".";
    yCurr += yStep; // shift y coordinate
  }
  // std::cout << std::endl;
  return nodes;
  /*
  // convert discrete pixel values (int) to doubles for calculation
  double r = static_cast<double>(_radius);
  double xRef = static_cast<double>(_referenceXDimension);
  double yRef = static_cast<double>(_referenceYDimension);

  // geometric calculations
  double xNum = std::floor(xRef / (2.0*r));
  double yNum = std::floor(((yRef/r) - 2.0)/sqrt(3.0) + 1.0);

  double totalNodes = xNum * yNum;

  _numberOfNodesX = static_cast<int>(xNum);
  _numberOfNodesY = static_cast<int>(yNum);
  _overhangX = static_cast<int>(xRef - (xNum * 2.0 * r));
  _overhangY = static_cast<int>(yRef - (2.0 + r * (sqrt(3.0)*(yNum - 1.0)))); //
  todo

  // catch edge case caused by shift in honeycomb tiling
  // if there is no room for an additional odd radius, less
  // circles actually fit in the area;
  int radiiInX = static_cast<int>(std::floor(xRef / r));
  if (radiiInX % 2 == 0) {
      _everySecondRowOneNodeLess = true;
      totalNodes -= std::floor(yNum / 2.0);
      _overhangX = static_cast<int>(xRef - ((xNum * 2.0 - 1.0) * r)); // todo
  }

  return static_cast<int>(totalNodes);
  */
}

size_t HoneyCombTiling::_findNumberOfNodes(int radius) {
  // std::cout << "finding number of nodes" << std::endl;
  return _tile(radius).size();
}

bool HoneyCombTiling::_circleIsInBound(int x, int y, int radius) {
  if (x - radius < 0 || y - radius < 0) {
    // std::cout << "out\n";
    return false;
  } else if (x + radius >= _referenceXDimension ||
             y + radius >= _referenceYDimension) {
    // std::cout << "out\n";
    return false;
  } else {
    // std::cout << "in\n";
    return true;
  }
}

bool HoneyCombTiling::_circleIsInBound(float xFloat, float yFloat, int radius) {
  int x = _nearestInt(xFloat);
  int y = _nearestInt(yFloat);
  // std::cout << "x,y = " << x << ", " << y << std::endl;
  // std::cout << "x-r,y-r = " << x - radius << ", " << y - radius << std::endl;
  if (x - radius < 0 || y - radius < 0) {
    // std::cout << "out\n";
    return false;
  } else if (x + radius >= _referenceXDimension ||
             y + radius >= _referenceYDimension) {
    // std::cout << "out\n";
    return false;
  } else {
    // std::cout << "in\n";
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
  // std::cout << "offsets: " << xOffset << ", " << yOffset << std::endl;
  // apply offset
  for (auto &entry : _nodes) {
    // std::cout << "entry.x = " << entry.x << std::endl;
    entry.x += xOffset;
    entry.y += yOffset;
    // std::cout << "entry.x = " << entry.x << std::endl << std::endl;
  }
}
