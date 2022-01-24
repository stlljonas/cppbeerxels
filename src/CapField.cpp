#include "CapField.h"
#include <functional>
#include <math.h>

void CapField::runCapShepherd() {
    std::cout << "capfield init\n";
    _capShepherd.init();
    std::cout << "processcaps\n";
    _capShepherd.processCaps();
}

void CapField::processReference() {
  // load image
  cv::Mat image = cv::imread(_referenceImagePath.string());
  // get tiling
  _honeyCombTiling.setDimensions(image.cols,
                                 image.rows); // maybe use cv::Mat::dims?
  _honeyCombTiling.setMaxNumNodes(_capShepherd.caps.size());
  std::cout << "optimal tiling\n";
  _honeyCombTiling.optimalTiling();
  int radius = _honeyCombTiling.getRadius();
  std::vector<cv::Point> optimalTiling = _honeyCombTiling.getNodes();
  std::cout << "number of nodes = " << optimalTiling.size() << std::endl;
  // for every node in the optimal tiling, create a smartcircle at that position
  for (const auto point : optimalTiling) {
    std::cout << "node\n";
    std::unique_ptr<SmartCircle> newCircle(new SmartCircle(point, radius));
    _referenceCircles.push_back(std::move(newCircle));
  }
}

void CapField::getPlacement() {
  std::vector<std::vector<double>> costMatrix = _computeCostMatrix();
  std::vector<int> assignment;

}

std::vector<std::vector<double>> CapField::_computeCostMatrix() {
  cv::Mat image = cv::imread(_referenceImagePath.string());
  size_t numCaps = _capShepherd.caps.size();
  size_t numCirc =  _referenceCircles.size();
  std::vector<std::vector<double>> costMatrix(numCaps,std::vector<double>(numCirc, 0));
  for (int i = 0; i < numCaps; ++i) {
    for (int j = 0; j < numCirc; ++j) {
      costMatrix[i][j] =
          _costFunction(_capShepherd.caps[i].get()->getAverageColor(),
                       _referenceCircles[j].get()->computeAverageColor(image));
    }
  }
  return costMatrix;
}

float CapField::_costFunction(const cv::Scalar a, const cv::Scalar b) {
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