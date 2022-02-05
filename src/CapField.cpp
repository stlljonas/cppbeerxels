#include "CapField.h"
#include <functional>
#include <math.h>

void CapField::runCapShepherd() {
  std::cout << "initializing capfield\n";
  _capShepherd.init();
  std::cout << "processing caps\n";
  _capShepherd.processCaps();
}

// @param numberOfNodes optional upper limit of possible nodes.
//  if not provided will be set equal to number of caps detected
void CapField::processReference(uint numberOfNodes) {
  std::cout << "processing reference image\n";
  // load image
  cv::Mat image = cv::imread(_referenceImagePath.string());
  // get tiling
  _honeyCombTiling.setDimensions(image.cols,
                                 image.rows); // maybe use cv::Mat::dims?
  std::cout << "target node number = ";
  if (numberOfNodes != 0) {
    _honeyCombTiling.setMaxNumNodes(numberOfNodes);
    std::cout << numberOfNodes << std::endl;
  } else {
    std::cout << _capShepherd.caps.size() << std::endl;
    _honeyCombTiling.setMaxNumNodes(_capShepherd.caps.size());
  }
  _honeyCombTiling.optimalTiling();
  int radius = _honeyCombTiling.getRadius();
  std::vector<cv::Point> optimalTiling = _honeyCombTiling.getNodes();
  std::cout << "optimal nodes number = " << optimalTiling.size() << std::endl;
  // for every node in the optimal tiling, create a smartcircle at that position
  for (const auto point : optimalTiling) {
    // std::cout << "node\n";
    std::unique_ptr<SmartCircle> newCircle(new SmartCircle(point, radius));
    _referenceCircles.push_back(std::move(newCircle));
  }
}

void CapField::computePlacement() {
  std::cout << "computing cap placement\n";
  std::vector<std::vector<double>> costMatrix = _computeCostMatrix();
  std::cout << "costMatrix size: " << costMatrix.size() << ", "
            << costMatrix[0].size() << std::endl;
  double cost = _hungAlgo.Solve(costMatrix, _placement);
  for (unsigned int x = 0; x < costMatrix.size(); x++)
    std::cout << x << "," << _placement[x] << "\t";
  std::cout << "\ncost: " << cost << std::endl;
}

void CapField::showCircleField() {
  cv::Mat image = cv::imread(_referenceImagePath.string());
  // std::cout << type2str(image.type()) << std::endl;
  popUpImage(image);
  cv::Mat circleField(image.size(), image.type(), {0, 0, 0});
  for (auto &pCircle : _referenceCircles) {
    SmartCircle circle = *pCircle.get();
    cv::circle(circleField, circle.getCenterPoint(), circle.getRadius(),
               circle.computeAverageColor(image), -1);
  }
  // std::cout << type2str(circleField.type()) << std::endl;
  popUpImage(circleField);
}

std::vector<std::vector<double>> CapField::_computeCostMatrix() {
  std::cout << "computing cost matrix\n";
  cv::Mat image = cv::imread(_referenceImagePath.string());
  size_t numCaps = _capShepherd.caps.size();
  size_t numCirc = _referenceCircles.size();
  std::cout << "size costmatrix: " << numCaps << ", " << numCirc << std::endl;
  std::vector<std::vector<double>> costMatrix(numCaps,
                                              std::vector<double>(numCirc, 0));
  for (int i = 0; i < numCaps; ++i) {
    for (int j = 0; j < numCirc; ++j) {
      // std::cout << "accessing cap/circle = " << i << "/" << j << std::endl;
      costMatrix[i][j] =
          _costFunction(_capShepherd.caps[i].get()->getAverageColor(),
                        _referenceCircles[j].get()->computeAverageColor(image));
    }
  }
  return costMatrix;
}

double CapField::_costFunction(const cv::Scalar a, const cv::Scalar b) {
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