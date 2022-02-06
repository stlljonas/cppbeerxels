#include "Flags.h"
#include <algorithm>

// set default values
VerbosityLevel Flags::VERBOSITY = NORMAL;
bool Flags::MANUAL_TUNING = false;    
bool Flags::DISPLAY = false;

void Flags::parseFlags(int &argc, char **argv) {
    std::vector<std::string> tokens;
    for (int i=1; i < argc; ++i) {
        tokens.push_back(std::string(argv[i]));
    }
    // Verbosity
    if (_isPresent(tokens, "-v")) {
        const std::string option = _getOption(tokens, "-v");
        if (option.compare("q") == 0) {
            VERBOSITY = QUIET;
        } else if (option.compare("n") == 0) {
            VERBOSITY = NORMAL;
        } else if (option.compare("v") == 0) {
            VERBOSITY = VERBOSE;
        } else if (option.compare("d") == 0) {
            VERBOSITY = DEBUG;
        }
    }    
    // Tuning
    if (_isPresent(tokens, "-t")) {
        MANUAL_TUNING = true;
    }
    // Display
    if (_isPresent(tokens, "-d")) {
        DISPLAY = true;
    }
}

bool Flags::_isPresent(const std::vector<std::string>& tokens, const std::string &option) {
    return std::find(tokens.begin(), tokens.end(), option)
        != tokens.end();
}

std::string Flags::_getOption(const std::vector<std::string>& tokens, const std::string& flag) {
    if (_isPresent(tokens,flag)) {
        std::vector<std::string>::const_iterator itr;
        itr = std::find(tokens.begin(), tokens.end(), flag);
        if (itr != tokens.end() && ++itr != tokens.end()){
            return *itr;
        }
    }
    std::string empty_string("");
    return empty_string;
}