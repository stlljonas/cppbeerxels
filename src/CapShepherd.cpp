#include "CapShepherd.h"
#include "Cerial.h"
#include <filesystem>

void CapShepherd::init() {
  Cerial::println("Initializing CapShepherd");

  const std::filesystem::path &path =
      _bottleCapDirectoryPath; // for readability

  for (const auto &file : std::filesystem::directory_iterator(path)) {

    if (file.is_regular_file()) {
      Cerial::print("Creating cap from file ",DEBUG);
      Cerial::println(file.path().filename().string(),DEBUG);
      std::unique_ptr<Cap> newCap(new Cap(file.path()));
      caps.push_back(std::move(newCap));
    }
  }
}

void CapShepherd::processCaps() {
  Cerial::println("Processing Caps");
  for (std::vector<std::unique_ptr<Cap>>::iterator cap = caps.begin();
       cap != caps.end(); ++cap) {
    cap->get()->analyze();
    Cerial::indicateProgress(NORMAL);
  }
  Cerial::endProgress(NORMAL);
}
