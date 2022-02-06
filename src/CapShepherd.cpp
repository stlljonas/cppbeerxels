#include "CapShepherd.h"
#include "Cerial.h"
#include <filesystem>

void CapShepherd::processCaps(bool tuning) {
  Cerial::println("Processing Caps");
  const std::filesystem::path &path =
      _bottleCapDirectoryPath; // for readability
  std::list<std::unique_ptr<Cap>>::iterator capIterator;

  // Instantiate caps from files
  for (const auto &file : std::filesystem::directory_iterator(path)) {

    if (file.is_regular_file()) {
      Cerial::print("Creating cap from file ",DEBUG);
      Cerial::println(file.path().filename().string(),DEBUG);
      std::unique_ptr<Cap> newCap(new Cap(file.path()));
      caps.push_back(std::move(newCap));
    }
  }

  // Initialize caps
  for (auto& cap : caps) {
    cap.get()->init();
  }
  
  // Tune cutout circles
  if (tuning) {
    capIterator = caps.begin();
    while (capIterator != caps.end()) {
      ReturnAction returnAction = capIterator->get()->tune();
      if (returnAction == RETUNE_PREVIOUS) {
        --capIterator;
      } else { 
        ++capIterator;
      }
    }
  }

  // Remove invalid caps
  capIterator = caps.begin();
  while (capIterator != caps.end()){
    if (capIterator->get()->isValid() == false) {
      // Remove cap and go to next element
      caps.erase(capIterator++);
    } else {
      ++capIterator;
    }
  }

  // Process caps
  for (auto& cap : caps) {
    cap.get()->process();
  }
}
