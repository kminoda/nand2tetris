#include "code.h"

std::map<std::string, std::string> dest_map{
    {"", "000"},
    {"null", "000"},
    {"M", "001"},
    {"D", "010"},
    {"MD", "011"},
    {"A", "100"},
    {"AM", "101"},
    {"AD", "110"},
    {"AMD", "111"}
};

std::map<std::string, std::string> jump_map{
    {"", "000"},
    {"null", "000"},
    {"JGT", "001"},
    {"JEQ", "010"},
    {"JGE", "011"},
    {"JLT", "100"},
    {"JNE", "101"},
    {"JLE", "110"},
    {"JMP", "111"}
};

std::map<std::string, std::string> comp_map{
    {"0",   "0101010"},
    {"1",   "0111111"},
    {"-1",  "0111010"},
    {"D",   "0001100"},
    {"A",   "0110000"},
    {"!D",  "0001101"},
    {"!A",  "0110001"},
    {"-D",  "0001111"},
    {"-A",  "0110011"},
    {"D+1", "0011111"},
    {"A+1", "0110111"},
    {"D-1", "0001110"},
    {"A-1", "0110010"},
    {"D+A", "0000010"},
    {"D-A", "0010011"},
    {"A-D", "0000111"},
    {"D&A", "0000000"},
    {"D|A", "0010101"},
    {"M",   "1110000"},
    {"!M",  "1110001"},
    {"-M",  "1110011"},
    {"M+1", "1110111"},
    {"M-1", "1110010"},
    {"D+M", "1000010"},
    {"D-M", "1010010"},
    {"M-D", "1000111"},
    {"D&M", "1000000"},
    {"D|M", "1010101"},
};

int stringToBinary(std::string str)
{
    int res = 0;
    int pow_two_n = 1;
    for (int i=str.size()-1; i>=0; i--)
    {
        if (str[i] == '1') res += pow_two_n;
        pow_two_n *= 2;
    }
    return res;
}

int binary_dest(std::string mnemonic)
{
    std::string str = dest_map[mnemonic];
    return stringToBinary(str);
}

int binary_comp(std::string mnemonic)
{
    std::string str = comp_map[mnemonic];
    return stringToBinary(str);
}

int binary_jump(std::string mnemonic)
{
    std::string str = jump_map[mnemonic];
    return stringToBinary(str);
}

// int main()
// {
//     return 0;
// }