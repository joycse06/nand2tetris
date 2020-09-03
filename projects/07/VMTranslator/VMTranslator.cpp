#include <iostream>
#include <fstream>
#include <string>
#include "StringUtils.h"
#include "Parser.h"
#include <filesystem>

void read_vm_lines(std::ifstream &vm_path_stream) {
  std::string current_line;
  std::cout << "Reading vm file: " << std::endl;

  while(std::getline(vm_path_stream, current_line)) {
    std::cout << current_line << std::endl; 
  }
}

int main(int argc, char** argv) {
  std::ifstream vm_file_stream;
  std::ofstream asm_file_stream;
  std::string vm_file_path;
  std::string asm_file_path;

  if(argc < 2) {
    std::cout << "Please invoke the program with a .vm file. e.g. VMTranslator somefile.vm";
    return 1;
  }

  vm_file_path = argv[1];
  vm_file_stream.open(vm_file_path);


  if (vm_file_stream.fail()) {
    std::cout << "Failed to open " << vm_file_path << ". Please make sure the file exist and have the correct permission.";
    return 1;
  }

  // read_vm_lines(vm_file_stream);
  // vm_file_stream.clear();
  // vm_file_stream.seekg(0);

  // output file path
  asm_file_path = std::filesystem::path(vm_file_path).replace_extension(".asm");
  asm_file_stream.open(asm_file_path);

  if (asm_file_stream.fail()) {
    std::cout << "Failed to open " << asm_file_path << ". Please make sure you have permission to create file.";
    return 1;
  }

  asm_file_stream << "Hello World 2!";
  std::cout << "Hello World 2!" << std::endl;

  // We can now proceed with parsing
  Parser parser(vm_file_stream);
  CommandType current_command_type;

  // enter into Parse -> CodeGen Loop
  while(parser.hasMoreCommands()) {
    parser.advance();
    current_command_type = parser.commandType();
    std::cout << std::endl;
    
    switch(current_command_type) {
      case C_ARITHMATIC:
        std::cout << "Arithmatic command!" << std::endl;
        break;
      case C_PUSH:
        std::cout << "Push command!" << std::endl;
        break;
      case C_POP:
        std::cout << "POP command!" << std::endl;
        break;
      default:
        std::cout << "Not-Interested command!" << std::endl;
    }
  }

  std::cout << "No Commands found" << std::endl;

  // clean up
  std::cout.flush();
  vm_file_stream.close();
  asm_file_stream.close();

  return 0;
}
