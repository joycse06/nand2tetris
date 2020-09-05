#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(std::ostream &file_stream) : asm_file_stream(file_stream) {
  this->segment_map["stack"] = 0;
  this->segment_map["local"] = 1;
  this->segment_map["argument"] = 2;
  this->segment_map["0"] = 3;
  this->segment_map["this"] = 3;
  this->segment_map["1"] = 4;
  this->segment_map["that"] = 4;
  this->segment_map["temp"] = 5;
}

std::string CodeGenerator::increment_sp() {
  std::string generated_code;
  generated_code.append("@0\n");
  generated_code.append("M=M+1");
  return generated_code;
}

std::string CodeGenerator::decrement_sp() {
  std::string generated_code;
  generated_code.append("@0\n");
  generated_code.append("M=M-1");
  return generated_code;
}

void CodeGenerator::writeArithmatic(std::string command) {
  int stack_segment_base_address;
  stack_segment_base_address = getSegmentBaseAddress("stack");

  if(command == "add" || command == "sub") {
    // pop second argument
    asm_file_stream << this->decrement_sp() << std::endl;
    asm_file_stream << "@" << stack_segment_base_address << std::endl;
    asm_file_stream << "A=M" << std::endl;
    asm_file_stream << "D=M" << std::endl;

    // pop first argument
    asm_file_stream << this->decrement_sp() << std::endl;
    asm_file_stream << "@" << stack_segment_base_address << std::endl;
    asm_file_stream << "A=M" << std::endl;

    // perform operation
    if( command == "add")
      asm_file_stream << "D=D+M" << std::endl;
    else
      asm_file_stream << "D=M-D" << std::endl;

    // push it to stack
    asm_file_stream << "M=D" << std::endl;

    // Increment stack pointer
    asm_file_stream << this->increment_sp() << std::endl;
  } else if (command == "neg") {
    asm_file_stream << "@" << stack_segment_base_address << std::endl;
    asm_file_stream << "A=M" << std::endl;
    asm_file_stream << "A=A-1" << std::endl;
    asm_file_stream << "M=-M" << std::endl;
  } else if (command == "eq") {
     
  } else if (command == "gt") {

  } else if (command == "lt") {
  
  } else if (command == "and") {

  } else if (command == "or") {

  } else if (command == "not") {

  } else {
    asm_file_stream << "Arithmatic command: " << command << std::endl;
  }
}

int CodeGenerator::getSegmentBaseAddress(std::string segment) {
  std::unordered_map<std::string, int>::const_iterator got = segment_map.find(segment);

  if (got == segment_map.end()) {
    throw std::runtime_error("Segment not found in map.");  
  } else {
    return got->second;
  }
}

void CodeGenerator::writePushPop(CommandType command, std::string segment, int index) {
  if(command != C_PUSH && command != C_POP) {
    throw std::runtime_error("Unknown command type in push/pop");
  }

  int segment_base_address;
  int stack_segment_base_address;
  asm_file_stream.flush();

  stack_segment_base_address = getSegmentBaseAddress("stack");

  switch(command) {
    case C_PUSH:
      // asm_file_stream << "PUSH" << " " << segment << " " << index << std::endl;
      // Load segment into D
      if (segment == "constant") {
        asm_file_stream << "@" << index << std::endl;
        asm_file_stream << "D=A" << std::endl;
        asm_file_stream << "@" << stack_segment_base_address << std::endl;
        asm_file_stream << "A=M" << std::endl;
        asm_file_stream << "M=D" << std::endl;
      } else if (segment == "temp") {
        segment_base_address = getSegmentBaseAddress(segment);
        int temp_address = segment_base_address + index;

        asm_file_stream << "@" << temp_address << std::endl;
        asm_file_stream << "D=M" << std::endl;
        asm_file_stream << "@" << stack_segment_base_address << std::endl;
        asm_file_stream << "A=M" << std::endl;
        asm_file_stream << "M=D" << std::endl;
      } else {
        segment_base_address = getSegmentBaseAddress(segment);
        asm_file_stream << "@" << index << std::endl;
        asm_file_stream << "D=A" << std::endl;
        asm_file_stream << "@" << segment_base_address << std::endl;
        asm_file_stream << "D=D+M" << std::endl;
        asm_file_stream << "A=D" << std::endl;
        asm_file_stream << "D=M" << std::endl;

        asm_file_stream << "@" << stack_segment_base_address << std::endl;
        asm_file_stream << "A=M" << std::endl;
        asm_file_stream << "M=D" << std::endl;
      }
      asm_file_stream << increment_sp() << std::endl;
      break;
    case C_POP:
      segment_base_address = getSegmentBaseAddress(segment);
      // Decrement SP, because value is at SP - 1, not SP
      asm_file_stream << decrement_sp() << std::endl;

      if (segment == "temp") {
        segment_base_address = getSegmentBaseAddress(segment);
        int temp_address = segment_base_address + index;

        // Load stack top address into A
        asm_file_stream << "@" << stack_segment_base_address << std::endl;
        asm_file_stream << "A=M" << std::endl;
        asm_file_stream << "D=M" << std::endl;

        asm_file_stream << "@" << temp_address << std::endl;
        asm_file_stream << "M=D" << std::endl;
      } else {
        // load calculated segment address into D
        asm_file_stream << "@" << index << std::endl;
        asm_file_stream << "D=A" << std::endl;
        asm_file_stream << "@" << segment_base_address << std::endl;
        asm_file_stream << "D=D+M" << std::endl;
        asm_file_stream << "@" << "13" << std::endl;
        asm_file_stream << "M=D" << std::endl;

        // Load stack top address into A
        asm_file_stream << "@" << stack_segment_base_address << std::endl;
        asm_file_stream << "A=M" << std::endl;
        asm_file_stream << "D=M" << std::endl;

        // Now swap them
        asm_file_stream << "@13" << std::endl;
        asm_file_stream << "A=M" << std::endl;
        asm_file_stream << "M=D" << std::endl;
      }
      break;
    default:
      throw std::runtime_error("Unknown command type in push/pop");
  }
}
