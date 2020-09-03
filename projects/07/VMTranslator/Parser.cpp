#include "Parser.h"
#include <iostream>

Parser::Parser(std::istream &file_stream) : vm_file_stream(file_stream) {
  // vm_file_stream = &file_stream;
  // vm_file_stream->clear();
  // vm_file_stream->seekg(0);
  // std::string temp;
  // if(std::getline(*vm_file_stream, temp))
  //   std::cout << "First Line: " << temp;
}

bool Parser::hasMoreCommands() {
  if (this->end_of_file_reached) return false;

  while(std::getline(vm_file_stream, this->next_line)) {
    if(!string_utils::is_comment_or_empty(this->next_line)) {
      string_utils::trim(this->next_line);
      return true;
    }
  }

  this->end_of_file_reached = true;
  return false;
}

void Parser::advance() {
  if (this->next_line == "") {
    throw std::runtime_error("Parsing Exception, advance() called with no next command");
  }

  std::string sanitised_line = string_utils::remove_inline_comment(this->next_line);

  std::string first_token;

  size_t pos = 0;
  pos = sanitised_line.find(" ");

  if(pos != std::string::npos) {
    first_token = sanitised_line.substr(0, pos);
  } else {
    first_token = sanitised_line;
  }

  if(first_token == "add" || first_token == "sub"
      || first_token == "neg"
      || first_token == "eq"
      || first_token == "gt"
      || first_token == "lt"
      || first_token == "and"
      || first_token == "or"
      || first_token == "not")
      this->current_command_type = C_ARITHMATIC;
  else if(first_token == "push")
    this->current_command_type = C_PUSH;
  else if(first_token == "pop")
    this->current_command_type = C_PUSH;
  else if (first_token == "label")
    this->current_command_type = C_PUSH;
  else if (first_token == "goto")
    this->current_command_type = C_GOTO;
  else if (first_token == "if")
    this->current_command_type = C_IF;
  else if (first_token == "function")
    this->current_command_type = C_FUNCTION;
  else if(first_token == "call")
    this->current_command_type = C_CALL;
  else if(first_token == "return")
    this->current_command_type = C_RETURN;
  else
    throw std::runtime_error("Unknown command found");

  std::cout << std::endl << "//" << sanitised_line;
  this->current_command = sanitised_line;
}

CommandType Parser::commandType() {
  return this->current_command_type;
}

std::string Parser::arg1() {
  return "first arg";
}

int Parser::arg2() { return 0; }


