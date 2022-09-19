#include "code_writer.h"
#include "vm_parser.h"

int main(int argc, char *argv[])
{
    std::string infile_name = argv[1];
    VMParser vm_parser(infile_name);
    CodeWriter code_writer(infile_name);
    while (vm_parser.hasMoreCommands())
    {
        vm_parser.advance();
        if (vm_parser.commandType() == "C_PUSH") code_writer.writePush(vm_parser.arg1(), vm_parser.arg2());
        else if (vm_parser.commandType() == "C_POP") code_writer.writePop(vm_parser.arg1(), vm_parser.arg2());
        else if (vm_parser.commandType() == "C_ARITHMETIC") code_writer.writeArithmetic(vm_parser.arg1());
    }

    code_writer.close();
}