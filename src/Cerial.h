#ifndef _CONSOLE_OUTPUT_H_
#define _CONSOLE_OUTPUT_H_

#include <opencv2/opencv.hpp>
#include "Flags.h"

// Cerial - It mimicks Arduino's Serial!

class Cerial {
  public:
    Cerial() = delete;
    static void indicateProgress(VerbosityLevel v = NORMAL);
    static void endProgress(VerbosityLevel v = NORMAL);
    template <typename T = char const* /*std::string*/>
    static void print(T output, VerbosityLevel v = NORMAL) {
      if (Flags::VERBOSITY >= v) {
        std::cout << output;
      }
    }
    template <typename T = char const* /*std::string*/>
    static void println(T output, VerbosityLevel v = NORMAL) {
      if (Flags::VERBOSITY >= v) {
        std::cout << output << std::endl;
      }
    }
    static void println(VerbosityLevel v = NORMAL);
    static void showImage(cv::Mat image, VerbosityLevel v = NORMAL, int milliSeconds = 0, bool alwaysShow = false);
    static bool isVerboseEnough(VerbosityLevel v = NORMAL);
    static void end();
};

#endif /* _CONSOLE_OUTPUT_H_ */