#include "symbol_table.h"

SymbolTable::SymbolTable()
{
    symbol_table["SP"] = 0;
    symbol_table["LCL"] = 1;
    symbol_table["ARG"] = 2;
    symbol_table["THIS"] = 3;
    symbol_table["THAT"] = 4;
    symbol_table["SCREEN"] = 16384;
    symbol_table["KBD"] = 24576;
    for (int i=0; i<15; i++)
    {
        std::string rn = "R" + std::to_string(i);
        symbol_table["rn"] = i;
    }
}

void SymbolTable::addEntry(std::string symbol, int address)
{
    symbol_table[symbol] = address;
}

bool SymbolTable::contains(std::string symbol)
{
    return symbol_table.count(symbol) != 0;
}

int SymbolTable::getAddress(std::string symbol)
{
    return symbol_table[symbol];
}

// int main()
// {
//     return 0;
// }