#include "code_writer.h"

std::map<std::string, std::string> register_name_map = {
    {"local", "LCL"},
    {"argument", "ARG"},
    {"this", "THIS"},
    {"that", "THAT"}
};

CodeWriter::CodeWriter(std::string infile) : ofs(getFileName(infile))
{
    setFileName(infile);
    stack_pointer = 256;    
    ofs << "// start here" << std::endl;
    ofs << "@" << stack_pointer << std::endl;
    ofs << "D=A" << std::endl;
    ofs << "@SP" << std::endl;
    ofs << "M=D" << std::endl;
}

std::string CodeWriter::getFileName(std::string infile_name)
{
    std::string outfile_name;
    int ext_dot_idx;
    for (int i=infile_name.size(); i>=0; i--) 
    {
        if (infile_name[i] == '.') 
        {
            ext_dot_idx=i;
            break;
        }
    }
    for (int j=0; j<ext_dot_idx; j++) outfile_name += infile_name[j];
    outfile_name += ".asm";
    return outfile_name;
}

void CodeWriter::setFileName(std::string infile_name)
{
    std::string outfile_name;
    int ext_dot_idx;
    for (int i=infile_name.size(); i>=0; i--) 
    {
        if (infile_name[i] == '.') 
        {
            ext_dot_idx=i;
            break;
        }
    }
    for (int j=0; j<ext_dot_idx; j++) 
    {
        if (infile_name[j] == '/') file_name_base = "";
        else file_name_base += infile_name[j];
    }
    for (int j=0; j<ext_dot_idx; j++) outfile_name += infile_name[j];
    outfile_name += ".asm";
    outfile_name = outfile_name;
}

void CodeWriter::writeArithmetic(std::string command)
{
    if (command=="add") writeCommandArg1Arg2("M=D+M", "sub");
    else if (command=="sub") writeCommandArg1Arg2("M=M-D", "sub");
    else if (command=="neg") writeCommandArg("M=-M", "neg");
    else if (command=="eq") writeCommand("JEQ", "less than");
    else if (command=="gt") writeCommand("JGT", "less than");
    else if (command=="lt") writeCommand("JLT", "less than");
    else if (command=="and") writeCommandArg1Arg2("M=D&M", "and");
    else if (command=="or") writeCommandArg1Arg2("M=D|M", "or");
    else if (command=="not") writeCommandArg("M=!D", "neg");
    curr_symbol_idx++;
}

void CodeWriter::writePush(std::string segment, int index)
{
    ofs << "// push " << segment << " " << index << std::endl;
    handleMemorySegmentMapping(segment, index);
    if (segment == "constant") ofs << "D=A" << std::endl;
    else ofs << "D=M" << std::endl;
    go2SP();
    ofs << "M=D" << std::endl; 
    forward();
}

void CodeWriter::writePop(std::string segment, int index)
{
    ofs << "// pop " << segment << " " << index << std::endl;
    back();
    go2SP();
    ofs << "D=M" << std::endl; 
    handleMemorySegmentMapping(segment, index);
    ofs << "M=D" << std::endl;
}

void CodeWriter::handleMemorySegmentMapping(std::string segment, int index)
{
    if (segment == "pointer" || segment == "temp")
    {
        ofs << "@" << pointerTempMap(segment, index) << std::endl;
    }
    else if (segment == "local" || segment == "argument" || segment == "this" || segment == "that") 
    {
        ofs << "@" << register_name_map[segment] << std::endl;
        ofs << "A=M" << std::endl; 
        for (int i=0; i<index; i++) ofs << "A=A+1" << std::endl;
    }
    else if (segment == "constant") 
    {
        ofs << "@" << index << std::endl;
    }
    else if (segment == "static")
    {
        ofs << "@" << file_name_base << "." << index << std::endl;
    }
}

std::string CodeWriter::pointerTempMap(std::string segment, int index)
{
    if (segment == "pointer" && index == 0) return "THIS";
    else if (segment == "pointer" && index == 1) return "THAT";
    else if (segment == "temp") return "R" + std::to_string(index+5);
    return "";
}

void CodeWriter::writeCommandArg(std::string opr, std::string comment="")
{
    ofs << "// " << comment << std::endl;
    back();
    go2SP();
    ofs << "D=M" << std::endl; 
    ofs << opr << std::endl;
    forward();
}

void CodeWriter::writeCommandArg1Arg2(std::string opr, std::string comment="")
{
    ofs << "// " << comment << std::endl;
    back();
    go2SP();
    ofs << "D=M" << std::endl; 
    back();
    go2SP();
    ofs << opr << std::endl;
    forward();
}

void CodeWriter::writeCommand(std::string opr, std::string comment="")
{
    ofs << "// " << comment << std::endl;
    back();
    go2SP();
    back();
    go2SP();
    ofs << "D=M-D" << std::endl;
    ofs << "M=-1" << std::endl;
    ofs << "@SKIP.TO." << curr_symbol_idx << std::endl;
    ofs << "D;" << opr << std::endl;
    go2SP();
    ofs << "M=0" << std::endl;
    ofs << "(SKIP.TO." << curr_symbol_idx << ")" << std::endl;
    forward();
}

void CodeWriter::go2SP()
{
    ofs << "@SP" << std::endl;
    ofs << "A=M" << std::endl; 
}

// void CodeWriter::fetchSPvalue()
// {
//     go2SP();
//     ofs << "M=D" << std::endl; 
// }

void CodeWriter::forward()
{
    ofs << "@SP" << std::endl;
    ofs << "M=M+1" << std::endl;
}

void CodeWriter::back() 
{
    ofs << "@SP" << std::endl;
    ofs << "M=M-1" << std::endl;
}

void CodeWriter::close()
{
    ofs << "(END)" << std::endl;
    ofs << "@END" << std::endl;
    ofs << "0;JMP" << std::endl;
    (ofs).close();
}