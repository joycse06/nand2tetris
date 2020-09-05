#include "Parser.h"
#include <iostream>

Parser::Parser(std::istream &file_stream) : vm_file_stream(file_stream) {
  // if this is not done, then it's garbage value will sometimes be true sometimes false
  // so will exhibit undefined behaviour

  this->end_of_file_reached = false;
  current_command_tokens.reserve(3);
}

std::string Parser::getCurrentCommand() {
  return current_command;
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
  current_command_tokens.clear();
  std::string current_token;
  std::stringstream ss(sanitised_line);

  while(std::getline(ss, current_token, ' ')) {
    this->current_command_tokens.push_back(current_token); 
  }

  first_token = current_command_tokens.at(0);

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
    this->current_command_type = C_POP;
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

  // std::cout << std::endl << "//" << sanitised_line;
  this->current_command = sanitised_line;
}

CommandType Parser::commandType() {
  return this->current_command_type;
}

std::string Parser::arg1() {
  if (this->current_command_tokens.size() > 1)
    return this->current_command_tokens.at(1); 
  else
    return this->current_command_tokens.at(0); 
}

int Parser::arg2() {
  return std::stoi(current_command_tokens.at(2));
}


