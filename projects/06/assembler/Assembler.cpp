#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <locale>

void read_asm_lines(std::string asm_path, std::vector<std::string> &asm_lines) {
  std::ifstream asm_file(asm_path);
  std::string current_line;

  while(std::getline(asm_file, current_line)) {
    asm_lines.push_back(current_line);
  }
}

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

bool is_comment_or_empty(std::string line) {
  trim(line);

  if (line.empty()) return true;
  if (line.find("//") == 0) return true;

  return false;
}

std::string remove_inline_comment(std::string line) {
  std::size_t pos = line.find("//");

  // return if not found
  if (pos == std::string::npos) return line;

  // do nothing if comment line
  if (pos == 0) return line;

  // otherwise remove everything from pos
  return trim_copy(line.substr(0, pos));
}

int main(int argc, char * argv[]) {
  if(argc < 2) {
    std::cout << "Please invoke the assembler with a path to an asm file.";
      return 1;
  }
  std::string asm_path = argv[1];
  std::vector<std::string> asm_lines;

  std::cout << "\nThis is my awesome assembler.";
  std::cout << "\nProcessing " << asm_path;

  std::cout << "\nReading lines";
  read_asm_lines(asm_path, asm_lines);

  std::cout << "\nPrinting lines of the asm file...\n";

  for(auto line : asm_lines)
    if(!is_comment_or_empty(line))
        std::cout << remove_inline_comment(line) << std::endl;

  return 0;
}
