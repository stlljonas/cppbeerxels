#ifndef _CAP_FIELD_H_
#define _CAP_FIELD_H_

#include "CapShepherd.h"
#include "Hungarian.h"
#include "SmartCircle.h"
#include "Tiling.h"
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <vector>

class Field {
public:
  Field() = delete;
  Field(std::filesystem::path referenceFilePath_,
           std::filesystem::path bottleCapDirectoryPath_)
      : _referenceImagePath(referenceFilePath_),
        _capShepherd(bottleCapDirectoryPath_){};
  // create caps and cut them out
  void runCapShepherd();
  // load reference, find optimal tiling,
  // create smart circles at tiling nodes
  void processReference(uint numberOfNodes = 0);
  // calls munkres to find placement of caps in field
  void computePlacement();
  // show placement using average colors
  cv::Mat computeCircleField();
  // show field using the actual caps
  cv::Mat computeField();

private:
  CapShepherd _capShepherd;
  std::vector<std::unique_ptr<SmartCircle>> _referenceCircles;
  HoneyCombTiling _honeyCombTiling;
  std::vector<int> _placement;
  const std::filesystem::path _referenceImagePath;
  cv::Size _referenceImageSize;

  // munkres lib object?
  HungarianAlgorithm _hungAlgo;
  std::vector<std::vector<double>> _computeCostMatrix();
  double _costFunction(const cv::Scalar a, const cv::Scalar b);
};

#endif /* _CAP_FIELD_H_ */