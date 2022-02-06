#include "Field.h"
#include "CapShepherd.h"
#include "Cerial.h"
#include "helpers.h"
#include <chrono>
#include <iostream>


int main(int argc, char **argv) {
  auto start = std::chrono::high_resolution_clock::now();
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
  auto end = std::chrono::high_resolution_clock::now();
  auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
  std::cout << "Program ran for " << ms_int << " milliseconds\n";
}