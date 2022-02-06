#include "Field.h"
#include <functional>
#include <math.h>
#include "Cerial.h"

void Field::runCapShepherd() {
  _capShepherd.processCaps();
}

// @param numberOfNodes optional upper limit of possible nodes.
//  if not provided will be set equal to number of caps detected
void Field::processReference(uint numberOfNodes) {
  Cerial::println("Processing reference image", NORMAL);
  // load image
  cv::Mat image = cv::imread(_referenceImagePath.string());
  Cerial::showImage(image, NORMAL, 500);
  _referenceImageSize = image.size();
  Cerial::println<cv::Size_<int>>(_referenceImageSize, DEBUG);
  // get tiling
  _honeyCombTiling.setDimensions(image.cols,
                                 image.rows); // maybe use cv::Mat::dims?
  Cerial::print("Target node number = ", VERBOSE);
  if (numberOfNodes != 0) {
    _honeyCombTiling.setMaxNumNodes(numberOfNodes);
    Cerial::println<uint>(numberOfNodes, VERBOSE);
  } else {
    Cerial::println<uint>(_capShepherd.caps.size(), VERBOSE);
    _honeyCombTiling.setMaxNumNodes(_capShepherd.caps.size());
  }
  _honeyCombTiling.optimalTiling();
  int radius = _honeyCombTiling.getRadius();
  std::vector<cv::Point> optimalTiling = _honeyCombTiling.getNodes();
  
  // for every node in the optimal tiling, create a smartcircle at that position
  Cerial::println("Creating SmartCircles in node positions", DEBUG);
  for (const auto point : optimalTiling) {
    Cerial::indicateProgress(DEBUG);
    std::unique_ptr<SmartCircle> newCircle(new SmartCircle(point, radius));
    _referenceCircles.push_back(std::move(newCircle));
  }
  Cerial::endProgress(DEBUG);
}

void Field::computePlacement() {
  Cerial::println("Computing cap placement\n");

  std::vector<std::vector<double>> costMatrix = _computeCostMatrix();
  
  Cerial::print("costMatrix size: ", DEBUG);
  Cerial::print<std::size_t>(costMatrix.size(), DEBUG);
  Cerial::print(", ", DEBUG);
  Cerial::println<std::size_t>(costMatrix[0].size(), DEBUG);

  double cost = _hungAlgo.Solve(costMatrix, _placement);

  for (unsigned int x = 0; x < costMatrix.size(); x++) {
    Cerial::print<unsigned int>( x, VERBOSE);
    Cerial::print( ",", VERBOSE);
    Cerial::print<int>( _placement[x], VERBOSE);
    Cerial::print( "\t", VERBOSE);
  }
  Cerial::println(VERBOSE);
  Cerial::print("Cost: ", VERBOSE);
  Cerial::println<double>(cost, VERBOSE);
}

cv::Mat Field::computeCircleField() {

  Cerial::println("Computing circle field");

  cv::Mat image = cv::imread(_referenceImagePath.string());
  cv::Mat circleField(image.size(), image.type(), {0, 0, 0});
  for (auto &pCircle : _referenceCircles) {
    Cerial::showImage(circleField,VERBOSE, 50);
    SmartCircle circle = *pCircle.get();
    cv::circle(circleField, circle.getCenterPoint(), circle.getRadius(),
               circle.computeAverageColor(image), -1);
  }
  Cerial::showImage(circleField,NORMAL,500);
  return circleField;
}

cv::Mat Field::computeField() {
  Cerial::println("Computing cap field");
  cv::Mat capField(_referenceImageSize, CV_8UC3, {0, 0, 0});

  Cerial::showImage(capField, NORMAL, 200);  
  const int numberOfCaps =_capShepherd.caps.size();
  for (int i = 0; i < numberOfCaps; ++i) {
    Cerial::print("Placing cap  ", VERBOSE);
    Cerial::print<int>(i,VERBOSE);
    Cerial::print(" in position ", VERBOSE);
    Cerial::print<int>(_placement[i],VERBOSE);
    if (_placement[i] < 0) {
      Cerial::println(" .. abort",VERBOSE);
      continue;
    }
    Cerial::println(VERBOSE);
    SmartCircle referenceCircle = *_referenceCircles[_placement[i]].get();
    cv::Mat bottleCap = _capShepherd.caps[i].get()->getBottleCap();
    cv::Mat imageSection = capField(referenceCircle.regionOfInterest());
    int r = referenceCircle.getRadius();
    cv::Size size(2 * r + 1, 2 * r + 1);
    cv::Mat resizedBottleCap;
    cv::resize(bottleCap, resizedBottleCap, size);
    resizedBottleCap.copyTo(imageSection, referenceCircle.computeMask());
    Cerial::showImage(capField, NORMAL, 50);
  }
  return capField;
}

std::vector<std::vector<double>> Field::_computeCostMatrix() {
  cv::Mat image = cv::imread(_referenceImagePath.string());
  size_t numCaps = _capShepherd.caps.size();
  size_t numCirc = _referenceCircles.size();
  std::vector<std::vector<double>> costMatrix(numCaps,
                                              std::vector<double>(numCirc, 0));
  for (int i = 0; i < numCaps; ++i) {
    for (int j = 0; j < numCirc; ++j) {
      costMatrix[i][j] =
          _costFunction(_capShepherd.caps[i].get()->getAverageColor(),
                        _referenceCircles[j].get()->computeAverageColor(image));
    }
  }
  return costMatrix;
}

double Field::_costFunction(const cv::Scalar a, const cv::Scalar b) {
  return pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2) + pow(a[2] - b[2], 2);
}

/*
    Important: I need to know what munkres lib I will use
    such that I know how the api I'll use will look like.
    Need to make sure that my input data has the right type

    Use: https://github.com/mcximing/hungarian-algorithm-cpp
    Here we need to provide a preprocessed cost matrix. This should
    be rather straight forward given _capShepherd::_caps and
    _referenceCircles have been processed (I guess the averagecolors
    don't have to be precomputed. Generally, the matrix version is good
    as I don't need to provide a cost matrix etc. )
*/