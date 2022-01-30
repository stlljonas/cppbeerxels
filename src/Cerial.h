#ifndef _CONSOLE_OUTPUT_H_
#define _CONSOLE_OUTPUT_H_

#include <opencv2/opencv.hpp>

// Cerial - It mimicks Arduino's Serial!

enum VerbosityLevel {
    QUIET = 0,
    NORMAL = 1,
    VERBOSE = 2,
    DEBUG = 3
};

// rename to verbosity handler and or something similar
// and add option of calling popUpImage with a verbosity check
class Cerial {
  public:
    Cerial() = delete;
    static void indicateProgress(VerbosityLevel v = NORMAL);
    static void endProgress(VerbosityLevel v = NORMAL);
    template <typename T = char const* /*std::string*/>
    static void print(T output, VerbosityLevel v = NORMAL) {
      if (VERBOSITY >= v) {
        std::cout << output;
      }
    }
    template <typename T = char const* /*std::string*/>
    static void println(T output, VerbosityLevel v = NORMAL) {
      if (VERBOSITY >= v) {
        std::cout << output << std::endl;
      }
    }
    static void println(VerbosityLevel v = NORMAL);
    static void showImage(cv::Mat image, VerbosityLevel v = NORMAL, int milliSeconds = 0);
    static bool isVerboseEnough(VerbosityLevel v = NORMAL);
    static void end();
    static VerbosityLevel VERBOSITY;
};

#endif /* _CONSOLE_OUTPUT_H_ */