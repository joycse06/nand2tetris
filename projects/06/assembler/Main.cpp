#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <locale>
//#include "StringUtils.cpp"
#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"
#include <filesystem>

void read_asm_lines(std::string asm_path, std::vector<std::string> &asm_lines) {
  std::ifstream asm_file(asm_path);
  std::string current_line;

  while(std::getline(asm_file, current_line)) {
    asm_lines.push_back(current_line);
  }
}

std::string intTo15BitBinaryString(int address) {
  std::string temp;
  temp.reserve(15);
    
    for (int i = 14; i >= 0; i--) {
        int k = address >> i;
        if (k & 1)
            temp.append("1");
        else
            temp.append("0");
    }
  return temp;
}

int main(int argc, char * argv[]) {
  try {
    if(argc < 2) {
      std::cout << "Please invoke the assembler with a path to an asm file." << std::endl;
      return 1;
    }
    std::string asm_path = argv[1];
    std::vector<std::string> asm_lines;

    std::cout << "Processing " << asm_path << std::endl;

    Parser asm_parser(asm_path);
    Code code_generator;
    SymbolTable symbol_table;

    // First Pass
    // Build symbol table for labels
    // Now read with parser

    int running_line = -1;
    while (asm_parser.hasMoreCommands()) {
      asm_parser.advance();

      switch(asm_parser.commandType()) {
        case A_COMMAND:
        case C_COMMAND: 
          running_line++;
          break;
        case L_COMMAND: 
          symbol_table.addEntry(asm_parser.symbol(),running_line + 1);
          break;
        default:
          std::cout << "UnKNown type";
      }
    }


    namespace fs = std::filesystem;
    // second pass
    asm_parser.reset();
    std::ofstream hack_file(fs::path(asm_path).replace_extension(".hack"));
    std::string temp_symbol;
    std::string temp_comp_bits;
    std::string temp_jump_bits;
    std::string temp_dest_bits;

    int next_address = 16;
    int address;
    std::string binary;
    while (asm_parser.hasMoreCommands()) {
      asm_parser.advance();

      switch(asm_parser.commandType()) {
        case A_COMMAND:
          temp_symbol = asm_parser.symbol();
          if (std::isalpha(temp_symbol[0])) {
            if (symbol_table.contains(temp_symbol)) {
              address = symbol_table.getAddress(temp_symbol);  
            } else {
              address = next_address;
              symbol_table.addEntry(temp_symbol, address);
              next_address++;
            }
              binary = "0" + intTo15BitBinaryString(address);
            hack_file << binary << std::endl;
          } else {
              int converted_int = std::stoi(temp_symbol);
              binary = "0" + intTo15BitBinaryString(converted_int);
            hack_file << binary << std::endl;
          }
          break;
        case C_COMMAND: 
          temp_comp_bits = code_generator.comp(asm_parser.comp());
          temp_dest_bits = code_generator.dest(asm_parser.dest());
          temp_jump_bits = code_generator.jump_(asm_parser.jump_());
          hack_file << "111" << temp_comp_bits << temp_dest_bits << temp_jump_bits << std::endl;
          break;
        case L_COMMAND:
          continue;
        default:
          std::cout << "UnKNown type";
      }
    }

    std::cout << "\nFinished writing..." << fs::path(asm_path).replace_extension(".hack") << std::endl;
  }
  catch( const std::exception & ex ) {
    std::cout << "Error happened";
    std::cout << ex.what() << std::endl;
    return 1;
  }
  // Second Pass
  // handle variables and code generation

  return 0;
}
