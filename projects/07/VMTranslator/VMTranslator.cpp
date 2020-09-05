#include <iostream>
#include <fstream>
#include <string>
#include "StringUtils.h"
#include "Parser.h"
#include "CodeGenerator.h"
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

  // asm_file_stream << "Hello World 2!";
  // std::cout << "Hello World 2!" << std::endl;

  std::string temp;

  // std::getline(vm_file_stream, temp);

  // std::cout << "First Line: " << temp << std::endl;

  // We can now proceed with parsing
  Parser parser(vm_file_stream);
  CommandType current_command_type;
  // CodeGenerator code_generator(std::cout);
  CodeGenerator code_generator(asm_file_stream);

  // enter into Parse -> CodeGen Loop
  while(parser.hasMoreCommands()) {
    parser.advance();
    asm_file_stream << "// " << parser.getCurrentCommand() << std::endl;
    // std::cout << std::endl << "// " << parser.getCurrentCommand() << std::endl;
    current_command_type = parser.commandType();
    
    switch(current_command_type) {
      case C_ARITHMATIC:
        // std::cout << "Arithmatic command! arg1: " << parser.arg1() << std::endl;
        code_generator.writeArithmatic(parser.arg1());
        break;
      case C_PUSH:
      case C_POP:
        code_generator.writePushPop(current_command_type, parser.arg1(), parser.arg2());
        break;
      default:
        std::cout << "Not-Interested command!" << std::endl;
    }
  }

  // clean up
  std::cout.flush();
  vm_file_stream.close();
  asm_file_stream.close();

  return 0;
}
