#include <fstream>
#include <string>
#include "StringUtils.h"

enum CommandType { C_ARITHMATIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL };

class Parser {
  private:
    std::istream &vm_file_stream;
    std::string current_command;
    CommandType current_command_type;
    std::string next_line;
    bool end_of_file_reached;

  public:
    Parser(std::istream &file_stream);
    void advance();
    bool hasMoreCommands();
    CommandType commandType();
    std::string arg1();
    int arg2();
};
