#include "Cerial.h"
#include <thread>
#include <chrono>
#include <iostream>

void Cerial::indicateProgress(VerbosityLevel v) {
    if (Flags::VERBOSITY >= v) { 
        std::cout << ".";
        std::cout.flush();
    }
}

void Cerial::endProgress(VerbosityLevel v) {
    if (Flags::VERBOSITY >= v) { 
        std::cout << "done\n";
    }
}
/*
template <typename T>
void Cerial::print(T output, Level v) {
    if ( >= v) {
        std::cout << output;
    }
}

template <typename T>
void Cerial::println(T output, VerbosityLevel v) {
    if (Flags::VERBOSITY >= v) {
        std::cout << output << std::endl;
    }
}
*/
void Cerial::println(VerbosityLevel v) {
    if (Flags::VERBOSITY >= v) {
        std::cout << std::endl;
    }
}

void Cerial::showImage(cv::Mat image, VerbosityLevel v, int milliSeconds, bool alwaysShow) {
    if (Flags::VERBOSITY >= v &&
    (Flags::DISPLAY || alwaysShow)) {
        cv::imshow("image", image);
        cv::waitKey(milliSeconds);
    }
}

bool Cerial::isVerboseEnough(VerbosityLevel v) {
    return Flags::VERBOSITY >= v;
}

void Cerial::end() {
    cv::destroyAllWindows();
}