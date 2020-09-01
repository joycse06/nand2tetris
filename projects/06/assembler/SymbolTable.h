#include <fstream>
#include <string>
#include <algorithm>
#include <optional>
#include "StringUtils.cpp"
#include <unordered_map>

class SymbolTable {
  private:
    std::unordered_map<std::string, int> table;
  public:
    SymbolTable ();
    void addEntry(std::string symbol, int address);
    bool contains(std::string symbol);
    int getAddress(std::string symbol);
};

