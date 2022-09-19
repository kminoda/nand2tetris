#ifndef COMPILATION_ENGINE_H_
#define COMPILATION_ENGINE_H_

#include <string>
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <set>

#include "tokenizer.h"

class CompilationEngine
{
    private:
        std::ofstream ofs;
        Tokenizer tokenizer;
    public:
        CompilationEngine(std::string infile, std::string outfile);

        void compile();

        // program structure
        void compileClass();
        void compileClassVarDec();
        void compileType();
        void compileSubroutineDec();
        void compileParameterList();
        void compileSubroutineBody();
        void compileVarDec();

        // compile statements
        void compileStatements();
        void compileLet();
        void compileIf();
        void compileWhile();
        void compileDo();
        void compileReturn();

        // equation
        void compileExpression();
        void compileTerm();
        void compileSubroutineCall();
        void compileExpressionList();

        // others
        void compileIdentifier();
        void compileSymbol();
        void compileKeyWord();
        void compileBeginning(std::string str);
        void compileEnd(std::string str);

        bool isStatement();
        bool isOperator();
};

#endif // COMPILATION_ENGINE_H_