#include "CapShepherd.h"
#include <filesystem>
#include <iostream>

void CapShepherd::init() {

  const std::filesystem::path &path =
      _bottleCapDirectoryPath; // for readability

  for (const auto &file : std::filesystem::directory_iterator(path)) {

    if (file.is_regular_file()) {
      std::cout << "Creating cap from file " << file.path().filename().string() << std::endl;
      std::unique_ptr<Cap> newCap(new Cap(file.path()));
      caps.push_back(std::move(newCap));
    }
  }
}

void CapShepherd::processCaps() {
  std::cout << "Processing Caps:\n";
  for (std::vector<std::unique_ptr<Cap>>::iterator cap = caps.begin();
       cap != caps.end(); ++cap) {
    cap->get()->analyze();
    std::cout << ".";
    std::cout.flush();
  }
  std::cout << " done" << std::endl;
}
