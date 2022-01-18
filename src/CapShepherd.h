#ifndef _CAP_SHEPHERD_H_
#define _CAP_SHEPHERD_H_

#include "Cap.h"
#include <vector>
#include <memory>
#include <filesystem>

class CapShepherd
{
public:
    CapShepherd(std::string rawImagesDirectoryPath) : _rawImagesDirectoryPath(rawImagesDirectoryPath){};
    // find files, and initialize caps with correct paths in _caps
    void init();
    // call cap methods
    void processCaps();
    // delete all computed images (keep raws)
    void purge();
    // return _caps
    std::vector<std::unique_ptr<Cap>> getCaps();

private:
    std::string _rawImagesDirectoryPath;
    std::vector<std::unique_ptr<Cap>> _caps;
};

#endif /* _CAP_SHEPHERD_H_ */
