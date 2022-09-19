#include "vm_parser.h"

bool isSpace(unsigned char c)
{
    return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == 'f');
}

std::string removeSpaces(std::string input)
{
    int start = -1;
    int end = -1;
    int count = 0;
    for (char x : input) 
    {
        if (!isSpace(x) && start<0) start = count;
        if (!isSpace(x)) end = count;
        count++;
    }
    input = input.substr(start, end-start+1);
    return input;
}

std::string removeCommentOuts(std::string input)
{
    if (input.find("//") == std::string::npos) return input;
    else return input.substr(0, input.find("//")-1);
}

VMParser::VMParser(std::string infile)
{
    std::ifstream ifs(infile);
    std::string str;
    while(getline(ifs, str)) {
        if (str.substr(0, 2) == "//" || str.size()==1) continue;
        str = removeCommentOuts(str);
        str = removeSpaces(str);
        commands.push(str);
    }
}

void VMParser::splitCommand()
{
    curr_command_words = {};
    std::string curr_command_temp = curr_command;
    while(curr_command_temp.find(" ") != std::string::npos)
    {
        int next_index = curr_command_temp.find(" ");
        std::string new_word = curr_command_temp.substr(0, next_index);
        curr_command_temp = curr_command_temp.substr(next_index+1, curr_command_temp.size()-next_index);
        curr_command_words.push_back(new_word);
    }
    curr_command_words.push_back(curr_command_temp);
}

bool VMParser::hasMoreCommands()
{
    return !commands.empty();
}

void VMParser::advance()
{
    curr_command = commands.front(); commands.pop();
    splitCommand();
    return;
}

std::string VMParser::commandType()
{
    if (curr_command.substr(0, 3) == "pop") return "C_POP";
    else if (curr_command.substr(0, 4) == "push") return "C_PUSH";
    else if (curr_command.substr(0, 8) == "function") return "C_FUNCTION";
    else if (curr_command.substr(0, 5) == "label") return "C_LABEL";
    else if (curr_command.substr(0, 4) == "goto") return "C_GOTO";
    else if (curr_command.substr(0, 6) == "return") return "C_RETURN";
    else if (curr_command.substr(0, 2) == "if") return "C_IF";
    else if (curr_command.substr(0, 4) == "call") return "C_CALL";
    else return "C_ARITHMETIC";
}


std::string VMParser::arg1()
{
    if (commandType()=="C_ARITHMETIC") return curr_command;
    else if (curr_command_words.size() > 1) return curr_command_words[1];
    else return "";
}

int VMParser::arg2()
{
    if (curr_command_words.size() > 2) return std::stoi(curr_command_words[2]);
    else return 0;
}

// int main()
// {
//     VMParser vm_parser("../StackArithmetic/SimpleAdd/SimpleAdd.vm");
//     while (vm_parser.hasMoreCommands())
//     {
//         vm_parser.advance();
//         std::cout << vm_parser.arg1() << " " << vm_parser.arg2() << std::endl;
//     }
// }