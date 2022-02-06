#ifndef _FLAGS_H_
#define _FLAGS_H_

#include <string>
#include <vector>

enum VerbosityLevel {
    QUIET = 0,
    NORMAL = 1,
    VERBOSE = 2,
    DEBUG = 3
};

class Flags {
  public:
    Flags() = delete;
    static VerbosityLevel VERBOSITY;
    static bool MANUAL_TUNING;
    static bool DISPLAY;
    static void parseFlags(int &argc, char **argv);
  private:
    static bool _isPresent(const std::vector<std::string>& tokens, const std::string &option);
    static std::string _getOption(const std::vector<std::string>& tokens, const std::string &option);
};

#endif /* _FLAGS_H_ */