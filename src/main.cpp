#include "Field.h"
#include "CapShepherd.h"
#include "Cerial.h"
#include "helpers.h"
#include <chrono>
#include <iostream>


int main(int argc, char **argv) {
  auto start = std::chrono::high_resolution_clock::now();
  Flags::parseFlags(argc, argv);

  std::filesystem::path workingDirectory = std::filesystem::current_path();
  
  std::filesystem::path referenceImageFilePath = workingDirectory / "data/reference/baboon.tiff";
  
  std::filesystem::path bottleCapDirectoryPath = workingDirectory / "data/raw/";

  std::filesystem::path outputFilePath = workingDirectory / "/data/res.png";

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
  std::cout << "Program ran for " << ms_int.count() << " milliseconds\n";
}