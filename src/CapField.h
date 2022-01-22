#ifndef _CAP_FIELD_H_
#define _CAP_FIELD_H_

#include <filesystem>
#include <vector>
#include <opencv2/opencv.hpp>
#include "Tiling.h"

class CapField {
  public:
    CapField(std::filesystem::path referenceImagePath_) : referenceImagePath(referenceImagePath_) {};
    std::vector<cv::Scalar> referenceTargetColors;
    std::filesystem::path referenceImagePath;
    HoneyCombTiling honeyCombTiling;
};

#endif /* _CAP_FIELD_H_ */