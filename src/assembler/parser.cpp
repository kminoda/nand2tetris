#include "parser.h"

Parser::Parser(std::string infile)
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

bool Parser::hasMoreCommands()
{
    return !commands.empty();
}

void Parser::advance()
{
    curr_command = commands.front(); commands.pop();
    return;
}

std::string Parser::commandType()
{
    if (curr_command.substr(0, 1) == "@") 
        return "A_COMMAND";
    else if (curr_command.substr(0, 1) == "(" && curr_command.substr(curr_command.size()-1, 1) == ")" )
        return "L_COMMAND";
    else 
        return "C_COMMAND";
}

std::string Parser::symbol()
{
    if (commandType() == "A_COMMAND")
        return curr_command.substr(1, curr_command.size()-1);
    else if (commandType() == "L_COMMAND")
        return curr_command.substr(1, curr_command.size()-2);
    return "";
}

std::string Parser::dest()
{
    if (curr_command.find("=") == std::string::npos) return "";
    int eq_index = curr_command.find("=");
    int semcol_index = curr_command.find(";");

    int cut_index = eq_index;
    if (eq_index == std::string::npos) cut_index = semcol_index;
    std::string dest_str = curr_command.substr(0, cut_index);
    return dest_str;
}

std::string Parser::comp()
{
    int eq_index = -1;
    if (curr_command.find("=") != std::string::npos) eq_index = curr_command.find("=");
    int semcol_index = curr_command.find(";");
    std::string comp_str = curr_command.substr(eq_index+1, semcol_index - eq_index - 1);
    return comp_str;
}

std::string Parser::jump()
{
    if (curr_command.find(";") == std::string::npos) return "";
    int semcol_index = curr_command.find(";");
    std::string jump_str = curr_command.substr(semcol_index+1, curr_command.size() - semcol_index - 1);
    return jump_str;
}


bool isSpace(unsigned char c)
{
    return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == 'f');
}

std::string removeSpaces(std::string input)
{
    int count = 0;
    for (int i=0; i<input.size(); i++) if (!isSpace(input[i])) input[count++] = input[i];
    input.erase(count);
    return input;
}

std::string removeCommentOuts(std::string input)
{
    if (input.find("//") == std::string::npos) return input;
    else return input.substr(0, input.find("//")-1);
}

// int main()
// {
//     std::string infile_name = "../../add/Add.asm";
//     Parser parser(infile_name);

//     parser.advance();
//     std::cout << parser.commandType() << std::endl;
//     if (parser.commandType()=="C_COMMAND") std::cout << parser.dest() << " = " << parser.comp() << std::endl;
    
//     parser.advance();
//     std::cout << parser.commandType() << std::endl;
//     if (parser.commandType()=="C_COMMAND") std::cout << parser.dest() << " = " << parser.comp() << std::endl;

//     parser.advance();
//     std::cout << parser.commandType() << std::endl;
//     if (parser.commandType()=="C_COMMAND") std::cout << parser.dest() << " = " << parser.comp() << std::endl;
    
//     parser.advance();
//     std::cout << parser.commandType() << std::endl;
//     if (parser.commandType()=="C_COMMAND") std::cout << parser.dest() << " = " << parser.comp() << std::endl;
    
//     parser.advance();
//     std::cout << parser.commandType() << std::endl;
//     if (parser.commandType()=="C_COMMAND") std::cout << parser.dest() << " = " << parser.comp() << std::endl;

//     parser.advance();
//     std::cout << parser.commandType() << std::endl;
//     if (parser.commandType()=="C_COMMAND") std::cout << parser.dest() << " = " << parser.comp() << std::endl;

//     return 0;
// }
