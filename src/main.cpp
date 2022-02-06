#include "Field.h"
#include "CapShepherd.h"
#include "Cerial.h"
#include "helpers.h"
#include <iostream>


int main(int argc, char **argv) {
  Flags::parseFlags(argc, argv);

  std::filesystem::path referenceImageFilePath =
    "/home/jstolle/code/cppbeerxels/data/refernece/baboon.tiff";
  std::filesystem::path bottleCapDirectoryPath =
    "/home/jstolle/code/cppbeerxels/data-local/raw-orange/";

  std::filesystem::path outputFilePath = 
    "/home/jstolle/code/cppbeerxels/data/res.png";

  Field field(referenceImageFilePath, bottleCapDirectoryPath);
  field.runCapShepherd();
  field.processReference();
  field.computePlacement();
  cv::Mat circleField = field.computeCircleField();
  // popUpImage(circleField);
  cv::Mat capField = field.computeField();
  cv::imwrite(outputFilePath.string(), capField);
  Cerial::showImage(capField,NORMAL,0,true);
  //cv::imshow("new window",capField);
  Cerial::end();
}