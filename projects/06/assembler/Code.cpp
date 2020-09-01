#include <algorithm>
#include <iostream>
#include "Code.h"

Code::Code() {
  // Initialise comps, dests and jumps
  // a = 0
  comps["0"] =   "0101010";
  comps["1"] =   "0111111";
  comps["-1"] =  "0111010";
  comps["D"] =   "0001100";
  comps["A"] =   "0110000";
  comps["!D"] =  "0001101";
  comps["!A"] =  "0110001";
  comps["-D"] =  "0001111";
  comps["-A"] =  "0110011";
  comps["D+1"] = "0011111";
  comps["A+1"] = "0110111";
  comps["D-1"] = "0001110";
  comps["A-1"] = "0110010";
  comps["D+A"] = "0000010";
  comps["D-A"] = "0010011";
  comps["A-D"] = "0000111";
  comps["D&A"] = "0000000";
  comps["D|A"] = "0010101";

  // a = 1
  comps["M"] =   "1110000";
  comps["!M"] =  "1110001";
  comps["-M"] =  "1110011";
  comps["M+1"] = "1110111";
  comps["M-1"] = "1110010";
  comps["D+M"] = "1000010";
  comps["D-M"] = "1010011";
  comps["M-D"] = "1000111";
  comps["D&M"] = "1000000";
  comps["D|M"] = "1010101";

  // destinations
  dests["null"] = "000";
  dests["M"] = "001";
  dests["D"] = "010";
  dests["MD"] = "011";
  dests["A"] = "100";
  dests["AM"] = "101";
  dests["AD"] = "110";
  dests["AMD"] = "111";

  // jumps
  jumps["null"] = "000";
  jumps["JGT"] = "001";
  jumps["JEQ"] = "010";
  jumps["JGE"] = "011";
  jumps["JLT"] = "100";
  jumps["JNE"] = "101";
  jumps["JLE"] = "110";
  jumps["JMP"] = "111";
}


std::string Code::dest(std::string mnemonic) {
  std::unordered_map<std::string,std::string>::const_iterator got = dests.find(mnemonic);

  if (got == dests.end()) {
    throw "Couldn't find dest mnemonic: " + mnemonic;
  } else {
    return got->second;
  }
}

std::string Code::comp(std::string mnemonic) {
  std::unordered_map<std::string,std::string>::const_iterator got = comps.find(mnemonic);

  if (got == comps.end()) {
    throw "Couldn't find comp mnemonic: " + mnemonic;
  } else {
    return got->second;
  }
}


std::string Code::jump_(std::string mnemonic) {
  std::unordered_map<std::string,std::string>::const_iterator got = jumps.find(mnemonic);
  if (got == jumps.end()) {
    throw "Couldn't find jump mnemonic: " + mnemonic;
  } else {
    return got->second;
  }
}
