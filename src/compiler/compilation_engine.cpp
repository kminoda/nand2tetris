#include "compilation_engine.h"
#include "tokenizer.h"

CompilationEngine::CompilationEngine(std::string infile, std::string outfile) : ofs(outfile), tokenizer(infile)
{
    std::cout << "[CompilationEngine] Output file name: " << outfile << std::endl;
}

void CompilationEngine::compile()
{
    compileClass();
}

void CompilationEngine::compileClass()
{
    compileBeginning("class");
    compileKeyWord(); // 'class'
    compileIdentifier(); // 'className'
    compileSymbol(); // '{'
    while (tokenizer.symbol() != '}')
    {
        // classVarDec*
        if (tokenizer.keyWord()=="static" || tokenizer.keyWord()=="field")
        {
            compileClassVarDec(); 
        }
        // subroutineDec*
        else if (tokenizer.keyWord()=="constructor" || tokenizer.keyWord()=="function" || tokenizer.keyWord()=="method")
        {
            compileSubroutineDec();
        }
    }
    compileSymbol(); // '}'
    compileEnd("class");
}

void CompilationEngine::compileClassVarDec()
{
    compileBeginning("classVarDec");
    compileKeyWord(); // ('static' | 'field')
    compileType(); // type
    compileIdentifier(); // varName
    while (tokenizer.symbol() != ';') // (',' varName)*
    {
        compileSymbol();
        compileIdentifier();
    }
    compileSymbol(); // ';'
    compileEnd("classVarDec");
}

void CompilationEngine::compileType()
{
    if (tokenizer.keyWord()=="int" || tokenizer.keyWord()=="char" || tokenizer.keyWord()=="boolean")
    {
        compileKeyWord(); // 'int' | 'char' | 'boolean'
    }
    else
    {
        compileIdentifier(); // className
    }
}

void CompilationEngine::compileSubroutineDec()
{
    compileBeginning("subroutineDec");
    compileKeyWord(); // ('constructor' | 'function' | 'method')
    // ('void' | type)
    if (tokenizer.keyWord()=="void") compileKeyWord();
    else compileType();
    compileIdentifier(); // subroutineName
    compileSymbol(); // '('
    compileParameterList(); // parameterList
    compileSymbol(); // ')'
    compileSubroutineBody(); // subroutineBody
    compileEnd("subroutineDec");
}

void CompilationEngine::compileSubroutineBody()
{
    compileSymbol(); // '{'
    while (!isStatement()) // varDec*
    {
        compileVarDec();
    }
    compileStatements(); // statements
    compileSymbol(); // '}'
}

void CompilationEngine::compileParameterList()
{
    compileBeginning("parameterList");
    compileEnd("parameterList");
}

void CompilationEngine::compileVarDec()
{
    compileBeginning("varDec"); 
    compileKeyWord(); // 'var'
    compileType(); // type
    compileIdentifier(); // varName
    while (tokenizer.symbol() != ';') // (',' varName)*
    {
        compileSymbol();
        compileIdentifier();
    }
    compileSymbol(); // ';
    compileEnd("varDec");
}

void CompilationEngine::compileStatements()
{
    compileBeginning("statements");
    while(isStatement())
    {
        if (tokenizer.keyWord()=="let") compileLet();
        else if (tokenizer.keyWord()=="if") compileIf();
        else if (tokenizer.keyWord()=="while") compileWhile();
        else if (tokenizer.keyWord()=="do") compileDo();
        else if (tokenizer.keyWord()=="return") compileReturn();
    }
    compileEnd("statements");
}

void CompilationEngine::compileDo()
{
    compileBeginning("doStatement");
    compileKeyWord(); // 'do'
    compileSubroutineCall(); // subroutineCall
    compileSymbol(); // ';'
    compileEnd("doStatement");
}

void CompilationEngine::compileLet()
{
    compileBeginning("letStatement");
    compileKeyWord(); // 'let'
    compileIdentifier(); // varName
    if (tokenizer.symbol()=='=') // ('[' expression ']')?
    {
        compileSymbol();
        compileExpression();
        compileSymbol();
    }
    compileSymbol(); // '='
    compileExpression(); // expression
    compileSymbol(); // ';'
    compileEnd("letStatement");
}

void CompilationEngine::compileWhile()
{
    compileBeginning("whileStatement");
    compileKeyWord(); // 'while'
    compileSymbol(); // '('
    compileExpression(); // expression
    compileSymbol(); // ')'
    compileSymbol(); // '{'
    compileStatements(); // statements
    compileSymbol(); // '}'
    compileEnd("whileStatement");
}

void CompilationEngine::compileReturn()
{
    compileBeginning("returnStatement");
    compileKeyWord(); // 'return'
    if (tokenizer.symbol()!=';') 
    {
        compileExpression(); // expression
    }
    compileSymbol(); // ';'
    compileEnd("returnStatement");
}

void CompilationEngine::compileIf()
{
    compileBeginning("returnIf");
    compileKeyWord(); // 'if'
    compileSymbol(); // '('
    compileExpression(); // expression
    compileSymbol(); // ')'
    compileSymbol(); // '{'
    compileStatements(); // statements
    compileSymbol(); // '}'
    if (tokenizer.keyWord() == "else") // (’else’ ’{’ statements ’}’)?
    {
        compileKeyWord();  
        compileSymbol();
        compileStatements();
        compileSymbol();
    }
    compileEnd("returnIf");
}

void CompilationEngine::compileExpression()
{
    compileBeginning("expression");
    compileTerm(); // term
    while (isOperator()) // (op term)*
    {
        compileSymbol();
        compileTerm();
    }
    compileEnd("expression");
}

void CompilationEngine::compileTerm()
{
    if (tokenizer.symbol()=='-' || tokenizer.symbol()=='~') // unaryOp term
    {
        compileSymbol();
        compileTerm();
    }
    else if (tokenizer.symbol()=='[' || tokenizer.symbol()=='(') // '[' expression ']' | '(' expression ')'
    {
        compileSymbol();
        compileExpression();
        compileSymbol();
    }
}

void CompilationEngine::compileSubroutineCall()
{
    compileIdentifier(); // subroutineName or (className | varName)
    if (tokenizer.symbol()=='.')
    {
        compileSymbol(); // '.'
        compileIdentifier(); // subroutineName
    }
    compileSymbol(); // '('
    compileExpressionList(); // expressionList
    compileSymbol(); // ')'
}

void CompilationEngine::compileExpressionList()
{

}

void CompilationEngine::compileIdentifier()
{
    ofs << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
    tokenizer.advance();
}

void CompilationEngine::compileSymbol()
{
    ofs << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();
}

void CompilationEngine::compileKeyWord()
{
    ofs << "<keyword> " << tokenizer.keyWord() << " </keyword>" << std::endl;
    tokenizer.advance();
}

void CompilationEngine::compileBeginning(std::string str)
{
    ofs << "<" << str << ">" << std::endl;
}

void CompilationEngine::compileEnd(std::string str)
{
    ofs << "</" << str << ">" << std::endl;
}

bool CompilationEngine::isStatement()
{
    if (tokenizer.keyWord()=="let" || tokenizer.keyWord()=="if" || tokenizer.keyWord()=="else" || tokenizer.keyWord()=="while" || tokenizer.keyWord()=="do" || tokenizer.keyWord()=="return") 
    {
        return true;
    }
    else
    {
        return false;
    }   
}

bool CompilationEngine::isOperator()
{
    std::set<char> op_set = {'+', '-', '*', '/', '&', '|', '<', '>', '='};
    if (op_set.find(tokenizer.symbol()) != op_set.end()) 
    {
        return true;
    }
    else
    {
        return false;
    }   
}

int main(int argc, char *argv[])
{
    std::string infile_name = argv[1];
    std::string outfile_name = argv[2];
    CompilationEngine compilation_engine(infile_name, outfile_name);
    compilation_engine.compile();
}