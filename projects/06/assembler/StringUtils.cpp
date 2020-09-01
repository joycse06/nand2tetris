#ifndef STRING_UTILS
#define STRING_UTILS

#include <string>
#include <algorithm>
#include <cctype>
#include <locale>

namespace string_utils {
  static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
          return !std::isspace(ch);
          }));
  }

  static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
          return !std::isspace(ch);
          }).base(), s.end());
  }

  // was using .begin() and .end() instead of .rbegin() nad .rend()
  // static inline void rtrim(std::string &s) {
  //   s.erase(std::find_if(s.begin(), s.end(), [](unsigned char ch) {
  //     return !std::isspace(ch);
  //   }).base(), s.end());
  // }

  static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
  }

  // trim from both ends (copying)
  static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
  }

  static inline bool is_comment_or_empty(std::string line) {
    trim(line);

    if (line.empty()) return true;
    if (line.find("//") == 0) return true;

    return false;
  }

  static inline std::string remove_inline_comment(std::string line) {
    std::size_t pos = line.find("//");

    // return if not found
    if (pos == std::string::npos) return line;

    // do nothing if comment line
    if (pos == 0) return line;

    // otherwise remove everything from pos
    return trim_copy(line.substr(0, pos));
  }
}

#endif
