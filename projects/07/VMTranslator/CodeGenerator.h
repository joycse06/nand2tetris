#ifndef CODE_GENERATOR
#define CODE_GENERATOR

#include <string>
#include <iostream>
#include <unordered_map>
#include "Parser.h"

class CodeGenerator {
  private:
    std::unordered_map<std::string, int> segment_map;
    std::ostream &asm_file_stream;
    std::string file_name;
    int logical_jump_next_index;

    // manipulate SP pointer
    std::string increment_sp();
    std::string decrement_sp();
    int getSegmentBaseAddress(std::string segment);

  public:
    CodeGenerator(std::ostream &file_stream, std::string file_name);
    void writeArithmatic(std::string command);
    void writePushPop(CommandType command, std::string segment, int index);
};

#endif
