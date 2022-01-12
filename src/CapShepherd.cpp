#include "CapShepherd.h"
#include <filesystem>
#include <iostream>

void CapShepherd::init()
{
    const std::filesystem::path path = _rawImagesDirectoryPath;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::cout << "loop\n";
        const auto filenameStr = entry.path().filename().string();
        if (entry.is_regular_file()) {
            std::cout << "Found file " << filenameStr << std::endl;
            std::unique_ptr<Cap> newCap(new Cap(path.u8string() + filenameStr));
            _caps.push_back(std::move(newCap));
            _caps.back().get()->analyze(); // temp
        }
    }
    // iterate through _rawImagesPath directory
    // for every file (maybe check if it's a jpg)
        // push a new Cap with the corresponding path to 
        // _caps
    // done?
}

void CapShepherd::analyzeCaps() {
    for (std::vector<std::unique_ptr<Cap>>::iterator it = _caps.begin(); it != _caps.end(); ++it) {
        it->get()->analyze();
    }
}