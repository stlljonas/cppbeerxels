#ifndef _CAP_FIELD_H_
#define _CAP_FIELD_H_

#include "CapShepherd.h"
#include "SmartCircle.h"
#include "Tiling.h"
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <vector>
#include "Hungarian.h"

class CapField {
public:
  CapField() = delete;
  CapField(std::filesystem::path referenceFilePath_,
           std::filesystem::path bottleCapDirectoryPath_)
      : _referenceImagePath(referenceFilePath_),
        _capShepherd(bottleCapDirectoryPath_){};
  // create caps and cut them out 
  void runCapShepherd();
  // load reference, find optimal tiling,
  // create smart circles at tiling nodes
  void processReference();
  // calls munkres to find placement of caps
  // in field. More precisely, between
  // CapField::CapShepherd::_caps::getAverageColor()
  // and
  // CapField::_referenceCircles::computeAverageColor()
  void getPlacement();
  // void showPlacement();

private:
  CapShepherd _capShepherd;
  std::vector<std::unique_ptr<SmartCircle>> _referenceCircles;
  HoneyCombTiling _honeyCombTiling;
  std::vector<int> _placement;
  const std::filesystem::path _referenceImagePath;

  // munkres lib object?
  std::vector<std::vector<double>> _computeCostMatrix();
  float _costFunction(const cv::Scalar a, const cv::Scalar b);
};

#endif /* _CAP_FIELD_H_ */