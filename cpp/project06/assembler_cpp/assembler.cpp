#include "code.h"
#include "parser.h"
#include "symbol_table.h"
#include <cmath>
#include <cctype>
#include <algorithm>

std::string toBinary(int n)
{
    std::string str(16, '0');
    for (int i=15; i>=0; i--)
    {
        str[i] = (n%2==0 ?'0':'1');
        n /= 2;
    }
    return str;
}

int main(int argc, char *argv[])
{
    std::string infile_name = argv[1];
    std::string outfile_name;
    int ext_dot_idx;
    for (int i=infile_name.size(); i>=0; i--) 
    {
        if (infile_name[i] == '.') {ext_dot_idx=i; break;}
    }
    for (int j=0; j<ext_dot_idx; j++) outfile_name += infile_name[j];
    outfile_name += ".hack";

    // First loop
    Parser parser_for_table(infile_name);
    SymbolTable symbol_table;
    int curr_ad = 16;
    while(parser_for_table.hasMoreCommands())
    {
        parser_for_table.advance();
        // std::cout << "RAW: " << parser_for_table.curr_command << "\t\t\t";
        if (parser_for_table.commandType() == "C_COMMAND")
        {
            std::string dest = parser_for_table.dest();
            std::string comp = parser_for_table.comp();
            std::string jump = parser_for_table.jump();
            // std::cout << "dest: " << dest << ", comp: " << comp << ", jump: " << jump << std::endl;
        }
        else if (parser_for_table.commandType() == "L_COMMAND")
        {
            std::string symbol = parser_for_table.symbol();
            if (!symbol_table.contains(symbol)) symbol_table.addEntry(symbol, curr_ad); curr_ad++;
            // std::cout << "(" << symbol << ")" << std::endl;
        }
        else if (parser_for_table.commandType() == "A_COMMAND")
        {
            std::string symbol = parser_for_table.symbol();
            if (!symbol_table.contains(symbol)) symbol_table.addEntry(symbol, curr_ad); curr_ad++;
            // std::cout << "@" << symbol << std::endl;
        }
    }

    // Second loop
    Parser parser(infile_name);
    std::ofstream ofs(outfile_name);

    while(parser.hasMoreCommands())
    {
        parser.advance();

        int bit;
        if (parser.commandType() == "C_COMMAND")
        {
            std::string dest = parser.dest();
            std::string comp = parser.comp();
            std::string jump = parser.jump();
            // std::cout << "dest: " << dest << ", comp: " << comp << ", jump: " << jump << std::endl;
            // std::cout << binary_comp(comp) << std::endl;
            bit = pow(2, 13) + pow(2, 14) + pow(2, 15) + 
                  binary_comp(comp)*std::pow(2, 6) + 
                  binary_dest(dest)*std::pow(2, 3) + 
                  binary_jump(jump);
        }
        else if (parser.commandType() == "A_COMMAND")
        {
            std::string symbol = parser.symbol();
            if (std::all_of(symbol.cbegin(), symbol.cend(), isdigit))
            {
                bit = std::stoi(symbol);
            }
            else if (!symbol_table.contains(symbol)) 
            {
                symbol_table.addEntry(symbol, curr_ad); 
                curr_ad++;
                bit = symbol_table.getAddress(symbol);
            }
            // std::cout << "@" << symbol << std::endl;

        }    
        ofs << toBinary(bit) << std::endl;
    }
    ofs.close();

    return 0;
}