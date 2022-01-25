#include "CapField.h"
#include "CapShepherd.h"
#include "helpers.h"
#include <iostream>

int main() {
  std::filesystem::path referenceImageFilePath =
      "/home/jstolle/code/cppbeerxels/data/refernece/656189624.805342.jpg";
  std::filesystem::path bottleCapDirectoryPath =
      "/home/jstolle/code/cppbeerxels/data/raw/";

  CapField field(referenceImageFilePath, bottleCapDirectoryPath);
  field.runCapShepherd();
  field.processReference();
  field.computePlacement();
}