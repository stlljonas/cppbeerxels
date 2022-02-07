#include "CapShepherd.h"
#include "Cerial.h"
#include <filesystem>

void CapShepherd::processCaps() {
  const std::filesystem::path &path =
      _bottleCapDirectoryPath; // for readability
  std::list<std::unique_ptr<Cap>>::iterator capIterator;

  // Instantiate caps from files
  Cerial::println("Creating Cap objects from images");
  for (const auto &file : std::filesystem::directory_iterator(path)) {
    if (file.is_regular_file()) {
      Cerial::print("Creating cap from file ",DEBUG);
      Cerial::println(file.path().filename().string(),DEBUG);
      std::unique_ptr<Cap> newCap(new Cap(file.path()));
      caps.push_back(std::move(newCap));
    }
  }

  // Initialize caps
  Cerial::println("Initializing Caps");
  capIterator = caps.begin();
  while (capIterator != caps.end()){
    Cerial::indicateProgress();
    capIterator->get()->init();
    ++capIterator;
  }
  Cerial::endProgress();

  // Tune cutout circles
  if (Flags::MANUAL_TUNING) {
    std::cout << "Starting tuning process\n";
    std::cout << "Press 'c' at any time to see list of command options\n";    capIterator = caps.begin();
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
  Cerial::println("Removing invalid Caps");
  capIterator = caps.begin();
  while (capIterator != caps.end()){
    Cerial::indicateProgress();
    if (capIterator->get()->isValid() == false) {
      // Remove cap and go to next element
      caps.erase(capIterator++);
    } else {
      ++capIterator;
    }
  }
  Cerial::endProgress();

  // Process caps
  Cerial::println("Processing Caps");
  capIterator = caps.begin();
  while (capIterator != caps.end()) {
    Cerial::indicateProgress();
    capIterator->get()->process();
    ++capIterator;
  }
  Cerial::endProgress();
}
