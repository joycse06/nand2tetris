#include <algorithm>
#include <iostream>
#include "SymbolTable.h"

SymbolTable::SymbolTable() {
  // Initialise Symbol Table
  table["SP"] = 0;
  table["LCL"] = 1;
  table["ARG"] = 2;
  table["THIS"] = 3;
  table["THAT"] = 4;
  table["R0"] = 0;
  table["R1"] = 1;
  table["R2"] = 2;
  table["R3"] = 3;
  table["R4"] = 4;
  table["R5"] = 5;
  table["R6"] = 6;
  table["R7"] = 7;
  table["R8"] = 8;
  table["R9"] = 9;
  table["R10"] = 10;
  table["R11"] = 11;
  table["R12"] = 12;
  table["R13"] = 13;
  table["R14"] = 14;
  table["R15"] = 15;
  table["SCREEN"] = 16384;
  table["KBD"] = 24576;
}

void SymbolTable::addEntry(std::string symbol, int address) {
  table[symbol] = address;
}

bool SymbolTable::contains(std::string symbol) {
  std::unordered_map<std::string,int>::const_iterator got = table.find(symbol);

  if (got == table.end()) {
    return false;
  } else {
    return true;
  }
}

int SymbolTable::getAddress(std::string symbol) {
  return table[symbol];
}
