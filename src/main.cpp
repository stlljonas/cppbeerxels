#include "CapField.h"
#include "CapShepherd.h"
#include "helpers.h"
#include <iostream>

int main() {
  std::filesystem::path unprocessedReferencePath =
      "/home/jstolle/code/cppbeerxels/referece-image.jpg";
  std::filesystem::path referenceImageFilePath =
      "/home/jstolle/code/cppbeerxels/data/refernece/referece-image.jpg";
  std::filesystem::path bottleCapDirectoryPath =
      "/home/jstolle/code/cppbeerxels/data/raw/";

  resizeImage(unprocessedReferencePath, referenceImageFilePath, 0.25);

  CapField field(referenceImageFilePath, bottleCapDirectoryPath);
  
  field.runCapShepherd();

  //field.processReference(615);
  field.processReference();
  field.computePlacement();
  field.showCircleField();
  field.showCapField();
}