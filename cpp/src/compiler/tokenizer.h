#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <algorithm>
// #include <cctype>

class Tokenizer
{
    private:
        std::ifstream ifs;
        std::vector<std::string> input_script;
        std::queue<std::string> tokens;
        std::string infile_name;
    public:
        std::string curr_token;

        Tokenizer(std::string infile);
        void removeCommentOuts();  
        void tokenize();
        bool hasMoreTokens();
        void advance();
        std::string tokenType();
        std::string keyWord();
        char symbol();
        std::string identifier();
        int intVal();
        std::string stringVal();

        void debugger();
};

#endif // TOKENIZER_H_