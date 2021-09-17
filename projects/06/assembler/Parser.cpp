#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Parser.h"

Parser::Parser(std::string asm_file_path) {
  this->asm_file_ifstream = std::ifstream(asm_file_path);
  this->end_of_file_reached = false;
}

CommandType Parser::commandType() {
 return this->current_command_type;
}

std::string Parser::symbol() {
  if (this->current_command_type == A_COMMAND) {
      std::string symbol;
      symbol = this->current_command.substr(1);
    return symbol;
  } else if (this->current_command_type == L_COMMAND) {
    return this->current_command.substr(1, this->current_command.length() - 2);
  } else {
    throw std::runtime_error("Parsing exception, symbol() called for non A_COMMAND or L_COMMAND");
  }
}

std::string Parser::dest() {
  if (this->current_command_type == C_COMMAND) {
    std::string command = this->current_command;
    std::size_t posOfEqual = command.find("=");

    if (posOfEqual == std::string::npos) {
      return "null";
    } else {
      return command.substr(0, posOfEqual);
    }
  } else {
    throw std::runtime_error("Parsing exception, dest() called for non C_COMMAND");
  }
}

std::string Parser::comp() {
  if (this->current_command_type == C_COMMAND) {
    std::string command = this->current_command;
    std::size_t posOfEqual = command.find("=");
    std::size_t posOfSemicolon = command.find(";");

    if (posOfEqual != std::string::npos) {
      if (posOfSemicolon != std::string::npos) {
        return command.substr(posOfEqual + 1, (posOfSemicolon - posOfEqual - 1));
      } else {
        return command.substr(posOfEqual + 1);
      }
    } else {
      if(posOfSemicolon != std::string::npos) {
        return command.substr(0,posOfSemicolon);
      } else {
        return command;
      }
      
    }
  } else {
    throw std::runtime_error("Parsing exception, dest() called for non C_COMMAND");
  }
}

std::string Parser::jump_() {
  if (this->current_command_type == C_COMMAND) {
    std::string command = this->current_command;
    std::size_t posOfSemicolon = command.find(";");

    if (posOfSemicolon != std::string::npos) {
      return command.substr(posOfSemicolon + 1);
    } else {
      return std::string("null");
    }
  } else {
    throw std::runtime_error("Parsing exception, jump() called for non C_COMMAND");
  }
}

bool Parser::hasMoreCommands() {
  if(this->end_of_file_reached) return false;

   while(std::getline(this->asm_file_ifstream, this->next_line)) {
     if (!string_utils::is_comment_or_empty(this->next_line)) {
       string_utils::trim(this->next_line);
       return true;
     }
   }

   this->end_of_file_reached = true;
   return false;
}

void Parser::advance() {
  if (this->next_line == "") {
    throw std::runtime_error("Parsing exception, advance() called for with no next command");
  }

  std::string sanitised_line = string_utils::remove_inline_comment(this->next_line);
  char first_char = sanitised_line.at(0);

  if (first_char == '@') this->current_command_type = A_COMMAND;
  else if (first_char == '(') this->current_command_type = L_COMMAND;
  else this->current_command_type = C_COMMAND;

  this->current_command = sanitised_line;
}

void Parser::reset() {
  this->current_command = "";
  this->asm_file_ifstream.clear();
  this->asm_file_ifstream.seekg(0);
  this->end_of_file_reached = false;
}


