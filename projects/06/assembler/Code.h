#include <fstream>
#include <string>
#include <algorithm>
#include <optional>
#include "StringUtils.cpp"
#include <unordered_map>

class Code {
  private:
    std::unordered_map<std::string, std::string> dests;
    std::unordered_map<std::string, std::string> comps;
    std::unordered_map<std::string, std::string> jumps;

  public:
    Code ();
    std::string dest(std::string);
    std::string comp(std::string);
    std::string jump_(std::string);
};

