#include "code_writer.h"
#include "vm_parser.h"

#include <filesystem>

void write_code(CodeWriter *code_writer, VMParser *vm_parser)
{
    (*code_writer).setFileName((*vm_parser).infile_name);
    while ((*vm_parser).hasMoreCommands())
    {
        (*vm_parser).advance();
        if ((*vm_parser).commandType() == "C_PUSH") (*code_writer).writePush((*vm_parser).arg1(), (*vm_parser).arg2());
        else if ((*vm_parser).commandType() == "C_POP") (*code_writer).writePop((*vm_parser).arg1(), (*vm_parser).arg2());
        else if ((*vm_parser).commandType() == "C_ARITHMETIC") (*code_writer).writeArithmetic((*vm_parser).arg1());
        else if ((*vm_parser).commandType() == "C_LABEL") (*code_writer).writeLabel((*vm_parser).arg1());
        else if ((*vm_parser).commandType() == "C_GOTO") (*code_writer).writeGoto((*vm_parser).arg1());
        else if ((*vm_parser).commandType() == "C_IF") (*code_writer).writeIf((*vm_parser).arg1());
        else if ((*vm_parser).commandType() == "C_RETURN") (*code_writer).writeReturn();
        else if ((*vm_parser).commandType() == "C_FUNCTION") (*code_writer).writeFunction((*vm_parser).arg1(), (*vm_parser).arg2());
        else if ((*vm_parser).commandType() == "C_CALL") 
        {
            (*code_writer).writeCall((*vm_parser).arg1(), (*vm_parser).arg2());
        }
        else std::cout << "SOMETHING IS WRONG!" << std::endl;
    }    
}


int main(int argc, char *argv[])
{
    std::string infile_name = argv[1];
    std::filesystem::path infile_path = infile_name;
    CodeWriter code_writer(infile_name);
    code_writer.writeInit();
    if (infile_path.extension() == ".vm")
    {
        /* Here we compile one .vm file */
        VMParser vm_parser(infile_name);
        write_code(&code_writer, &vm_parser);
        code_writer.close();
    }
    else
    {
        /* Here we compile one or more .vm file in the designated directory */
        for(auto& file: std::filesystem::directory_iterator(infile_path))
        {
            if (file.path().extension() == ".vm") 
            {
                VMParser vm_parser(file.path().string());
                write_code(&code_writer, &vm_parser);
            }
        }
        code_writer.close();
    }
}