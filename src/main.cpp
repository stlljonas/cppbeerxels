#include "CapField.h"
#include "CapShepherd.h"
#include "Cerial.h"
#include "helpers.h"
#include <iostream>


int main(int argc, char **argv) {
    Cerial::VERBOSITY = NORMAL;
    if (argc > 1) {
        if (*argv[1] == 'q') {
            Cerial::VERBOSITY = QUIET;
        } else if (*argv[1] == 'v') {
            Cerial::VERBOSITY = VERBOSE;
        } else if (*argv[1] == 'd') {
            Cerial::VERBOSITY = DEBUG;
        }
    }
  std::filesystem::path unprocessedReferencePath =
      "/home/jstolle/code/cppbeerxels/referece-image.jpg";
  std::filesystem::path referenceImageFilePath =
      "/home/jstolle/code/cppbeerxels/data/refernece/referece-image.jpg";
  std::filesystem::path bottleCapDirectoryPath =
      "/home/jstolle/code/cppbeerxels/data/raw/";
  std::filesystem::path outputFilePath = 
      "/home/jstolle/code/cppbeerxels/data/res.png";

  resizeImage(unprocessedReferencePath, referenceImageFilePath, 0.25);

  CapField field(referenceImageFilePath, bottleCapDirectoryPath);
  field.runCapShepherd();
  std::cout << "Verbosity level " << Cerial::VERBOSITY << std::endl;

  field.processReference();
  field.computePlacement();
  cv::Mat circleField = field.computeCircleField();
  // popUpImage(circleField);
  cv::Mat capField = field.computeCapField();
  cv::imwrite(outputFilePath.string(), capField);
  Cerial::showImage(capField);
  //cv::imshow("new window",capField);
  std::cout << "done\n";
  Cerial::end();
}