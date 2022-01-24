#ifndef _CAP_SHEPHERD_H_
#define _CAP_SHEPHERD_H_

#include "Cap.h"
#include <filesystem>
#include <memory>
#include <vector>

class CapShepherd {
public:
  CapShepherd(std::filesystem::path bottleCapDirectoryPath_)
      : _bottleCapDirectoryPath(bottleCapDirectoryPath_){};
  // find files, and initialize caps with correct paths in _caps
  void init();
  // call cap methods
  void processCaps();
  // delete all computed images (keep raws)
  void purge();
  // void placeCaps(vector placement, target? (where to place them));
  std::vector<std::unique_ptr<Cap>> caps;

private:
  const std::filesystem::path _bottleCapDirectoryPath;
};

#endif /* _CAP_SHEPHERD_H_ */
