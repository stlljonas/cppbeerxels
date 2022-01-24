#include "CapField.h"
#include "CapShepherd.h"
#include "helpers.h"
#include <iostream>

int main() {
  /*Cap cap(7);
  cap.sourceImagePath =
  "/home/jstolle/code/cppbeerxels/data/raw/bottle-cap-2.jpg"; cap.analyze();
  cv::Mat bottleCapCutOut = cap.getBottleCap();
  cv::Mat averageColor(300,300, CV_8UC3, cap.getAverageColor());
  popUpImage(averageColor);
  */
  std::filesystem::path referenceImageFilePath  = "/home/jstolle/code/cppbeerxels/data/refernece/656189624.805342.jpg";
  std::filesystem::path bottleCapDirectoryPath = "/home/jstolle/code/cppbeerxels/data/raw/";
 
  CapField field(referenceImageFilePath,bottleCapDirectoryPath);
  std::cout << "running CapShepherd\n";
  field.runCapShepherd();
  std::cout << "processing reference\n";
  field.processReference();

  //HoneyCombTiling tiling(400, 500, 25);
  //tiling.optimalTiling();
  // tiling.showNodes();
}