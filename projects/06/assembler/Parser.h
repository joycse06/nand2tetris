#include <fstream>
#include <string>
#include <algorithm>
#include <optional>
#include "StringUtils.cpp"

enum CommandType { A_COMMAND, C_COMMAND, L_COMMAND };

class Parser {
  private:
    std::string current_command;
    std::string next_line;
    bool end_of_file_reached;
    CommandType current_command_type;
    std::ifstream asm_file_ifstream;

  public:
    Parser (std::string);
    void advance();
    bool hasMoreCommands();
    CommandType commandType();
    std::string symbol();
    std::string dest();
    std::string comp();
    std::string jump_();
    void reset();
};

