#include "tokenizer.h"

std::set<char> symbols = {
    '{', '}', '(', ')', '[', ']', '.', ',',
    ';', '+', '-', '*', '/', '&', '|', '<',
    '>', '=', '~'
};

std::set<std::string> keywords = {
    "class", "constructor", "function", "method", "field", "static",
    "var", "int", "char", "boolean", "void", "true", "false",
    "null", "this", "let", "do", "if", "else", "while", "return"
};

bool isSpace(const char c)
{
    return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v');
}

bool isInt(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    if (std::stoi(str)<0 || std::stoi(str)>32767) return false;
    return true;
}

class CommentOutDetector
{
    public:
        CommentOutDetector();
        void nextChar(char c);
        bool is_comment_out();
};

std::string removeOneLineCommentOuts(std::string input)
{
    if (input.find("//") == std::string::npos) return input;
    else return input.substr(0, input.find("//"));
}

Tokenizer::Tokenizer(std::string infile) : infile_name(infile), ifs(infile)
{
    std::cout << "[Tokenizer] File name: " << infile << std::endl;
    removeCommentOuts();

    tokenize();
}

void Tokenizer::removeCommentOuts()
{
    std::string str;
    char c_prev;
    bool is_comment_out = false;
    while(getline(ifs, str)) 
    {
        str = removeOneLineCommentOuts(str);
        std::string str_new;
        for (char c: str)
        {
            if (c == '*' && c_prev == '/') 
            {
                is_comment_out = true;
                str_new.pop_back();
            }
            if (!is_comment_out) str_new += c;
            if (c == '/' && c_prev == '*') 
            {
                is_comment_out = false;
                str_new += ' ';
            }
            c_prev = c;
        }
        input_script.push_back(str_new);
    }
}

void Tokenizer::tokenize()
{
    std::string token;
    for (std::string str : input_script) {
        token = "";
        for (char c : str)
        {
            if (isSpace(c)) 
            {
                if (token != "") // If c is space, and token is not empty
                {
                    tokens.push(token);
                    token = "";
                }
                else continue;
            }
            else if (symbols.count(c) == 1) // Current c is a symbol
            {
                if (token != "") tokens.push(token);
                token = "";
                std::string token{c};
                tokens.push(token);
                token = "";
            }
            else token += c;
        }
    }
    tokens.push(token);
}

bool Tokenizer::hasMoreTokens()
{
    return !tokens.empty();
}

void Tokenizer::advance()
{
    curr_token = tokens.front();
    tokens.pop();
}

std::string Tokenizer::tokenType()
{
    if (symbols.count(curr_token.c_str()[0]) == 1) return "SYMBOL";
    else if (keywords.count(curr_token) == 1) return "KEYWORD";
    else if (isInt(curr_token)) return "INT_CONST";
    else if (curr_token[0] == '"') return "STRING_CONST";
    else return "IDENTIFIER";
}

std::string Tokenizer::keyWord()
{
    std::string res = curr_token;
    transform(res.begin(), res.end(), res.begin(), toupper);
    return res;
}

char Tokenizer::symbol()
{
    return curr_token.c_str()[0];
}

std::string Tokenizer::identifier()
{
    return curr_token;
}

int Tokenizer::intVal()
{
    return std::stoi(curr_token);
}

std::string Tokenizer::stringVal()
{
    std::string res = curr_token;
    res.pop_back();
    return res.substr(1);
}

void Tokenizer::debugger()
{
    while(!tokens.empty())
    {
        std::cout << tokens.front() << std::endl;
        tokens.pop();
    }
}

// int main(int argc, char *argv[])
// {
//     std::string infile_name = argv[1];
//     Tokenizer tokenizer(infile_name);
//     tokenizer.advance();
//     while (tokenizer.hasMoreTokens())
//     {
//         std::cout << tokenizer.curr_token << " ";
//         if (tokenizer.tokenType() == "KEYWORD") std::cout << tokenizer.keyWord() << " ";
//         else if (tokenizer.tokenType() == "SYMBOL") std::cout << tokenizer.symbol() << " ";
//         else if (tokenizer.tokenType() == "IDENTIFIER") std::cout << tokenizer.identifier() << " ";
//         else if (tokenizer.tokenType() == "INT_CONST") std::cout << tokenizer.intVal() << " ";
//         else if (tokenizer.tokenType() == "STRING_CONST") std::cout << tokenizer.stringVal() << " ";
//         std::cout << tokenizer.tokenType() << std::endl;
//         tokenizer.advance();
//     }
// }