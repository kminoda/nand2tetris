#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

class SymbolTable
{
    private:
        std::map<std::string, int> symbol_table;
    public:
        SymbolTable();
        void addEntry(std::string symbol, int address);
        bool contains(std::string symbol);
        int getAddress(std::string symbol);
};

#endif // SYMBOL_TABLE_H_