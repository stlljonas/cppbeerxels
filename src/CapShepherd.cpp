#include "CapShepherd.h"
#include "Cerial.h"
#include <filesystem>

void CapShepherd::processCaps() {
  Cerial::println("Processing Caps");
  const std::filesystem::path &path =
      _bottleCapDirectoryPath; // for readability

  for (const auto &file : std::filesystem::directory_iterator(path)) {

    if (file.is_regular_file()) {
      Cerial::print("Creating cap from file ",DEBUG);
      Cerial::println(file.path().filename().string(),DEBUG);
      std::unique_ptr<Cap> newCap(new Cap(file.path()));
      newCap->analyze();
      if (newCap->isValid()) {
        caps.push_back(std::move(newCap));
      } else {
      } // newCap goes out of scope if not added to caps
    }
  }
}
