#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

class Parser
{
    public:
    // private:
        std::ifstream ifs;
        std::queue<std::string> commands;
        std::string curr_command;
    // public:
        Parser(std::string infile);
        bool hasMoreCommands();
        void advance();
        std::string commandType();
        std::string symbol();
        std::string dest();
        std::string comp();
        std::string jump();
};

bool isSpace(unsigned char c);
std::string removeSpaces(std::string input);
std::string removeCommentOuts(std::string input)

#endif // PARSER_H_