#ifndef VM_PARSER_H_
#define VM_PARSER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

class VMParser
{
    public:
        std::ifstream ifs;
        std::queue<std::string> commands;
        std::string curr_command;
        std::vector<std::string> curr_command_words;
        VMParser(std::string infile);
        void splitCommand();
        bool hasMoreCommands();
        void advance();
        std::string commandType();
        std::string arg1();
        int arg2();
};

#endif // VM_PARSER_H_