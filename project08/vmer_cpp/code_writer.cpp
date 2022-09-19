#include "code_writer.h"

std::map<std::string, std::string> register_name_map = {
    {"local", "LCL"},
    {"argument", "ARG"},
    {"this", "THIS"},
    {"that", "THAT"}
};

CodeWriter::CodeWriter(std::string infile) 
    : ofs(getFileName(infile)), stack_pointer(256)
{
}

std::string CodeWriter::getFileName(std::string infile_name)
{
    std::cout << "[CodeWriter] input file: " << infile_name << std::endl;
    std::filesystem::path infile_path = infile_name;
    std::string outfile_name;
    std::filesystem::path outfile_path;
    if (infile_path.extension() == ".vm")
    {
        /* is .vm file */
        is_directory = false;
        std::cout << "[CodeWriter] Compile .vm file" << std::endl;
        outfile_path = infile_path.parent_path();
    }
    else
    {
        /* is directory */
        is_directory = true;
        std::cout << "[CodeWriter] Compile directory" << std::endl;
        outfile_path = infile_path;
    }
    outfile_path.append(infile_path.stem().string());
    outfile_path += ".asm";
    outfile_name = outfile_path.string();
    std::cout << "[CodeWriter] output file: " << outfile_name << std::endl;
    return outfile_name;
}

void CodeWriter::setFileName(std::string infile_name)
{
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
}

void CodeWriter::writeInit()
{
    writeComment("initialization");
    getAddress(stack_pointer);
    updateValue("*SP");
    if (is_directory) 
    {
        at("Sys.init");
        jump();
    }
}

void CodeWriter::writePush(std::string segment, int index)
{
    writeComment("push " + segment + " " + std::to_string(index));
    handleMemorySegmentMapping(segment, index);
    if (segment == "constant") ofs << "D=A" << std::endl;
    else ofs << "D=M" << std::endl;
    updateValue("*SP");
    forward();
}

void CodeWriter::writePop(std::string segment, int index)
{
    writeComment("pop " + segment + " " + std::to_string(index));
    back();
    getValue("*SP");
    handleMemorySegmentMapping(segment, index);
    ofs << "M=D" << std::endl;
}

void CodeWriter::writeArithmetic(std::string command)
{
    if (command=="add") writeCommandArg1Arg2("M=D+M", "add");
    else if (command=="sub") writeCommandArg1Arg2("M=M-D", "sub");
    else if (command=="neg") writeCommandArg("M=-M", "neg");
    else if (command=="eq") writeCommand("JEQ", "equal");
    else if (command=="gt") writeCommand("JGT", "greater than");
    else if (command=="lt") writeCommand("JLT", "less than");
    else if (command=="and") writeCommandArg1Arg2("M=D&M", "and");
    else if (command=="or") writeCommandArg1Arg2("M=D|M", "or");
    else if (command=="not") writeCommandArg("M=!D", "not");
    curr_symbol_idx++;
}

void CodeWriter::writeLabel(std::string label, bool add_func_name)
{
    writeComment("writeLabel " + label);
    ofs << "(" << label << ")" << std::endl;
}

void CodeWriter::writeGoto(std::string label, bool add_func_name)
{
    writeComment("writeGoto " + label);
    at(label);
    jump();
}

void CodeWriter::writeIf(std::string label, bool add_func_name)
{
    writeComment("writeIf " + label);
    back();
    getValue("*SP");
    at(label);
    ofs << "D;JNE" << std::endl;
}

void CodeWriter::writeCall(std::string function_name, int num_args)
{
    writeComment("writeCall " + function_name + " " + std::to_string(num_args));
    std::string return_address_name = function_name + ".return-address." + std::to_string(curr_call_idx);
    curr_call_idx++;

    // push return-address
    getAddress(return_address_name);
    updateValue("*SP");
    forward();

    // push LCL
    getValue("LCL");
    updateValue("*SP");
    forward();

    // push ARG
    getValue("ARG");
    updateValue("*SP");
    forward();

    // push THIS
    getValue("THIS");
    updateValue("*SP");
    forward();

    // push THAT 
    getValue("THAT");
    updateValue("*SP");
    forward();

    // ARG = SP-n-5
    getValue("SP");
    addToD(-5 - num_args);
    updateValue("ARG");

    // LCL = SP
    getValue("SP");
    updateValue("LCL");

    writeGoto(function_name);
    writeLabel(return_address_name);
}

void CodeWriter::writeReturn()
{
    // func_name_stack.pop();
    writeComment("writeReturn");

    // FRAME = LCL
    getValue("LCL");
    updateValue("FRAME");

    // RET = *(FRAME-5)
    at(5);
    ofs << "D=D-A" << std::endl;
    ofs << "A=D" << std::endl;
    ofs << "D=M" << std::endl;
    updateValue("RET");

    // *ARG = pop()
    back();
    getValue("*SP");
    updateValue("*ARG");

    // SP = ARG + 1
    getValue("ARG");
    addToD(1);
    updateValue("SP");

    // THAT = *(FRAME - 1)  ==  THAT = SAVED_THAT
    getValue("FRAME");
    addToD(-1);
    ofs << "A=D" << std::endl;
    ofs << "D=M" << std::endl;
    updateValue("THAT");

    // THIS = *(FRAME - 2)  ==  THIS = SAVED_THIS
    getValue("FRAME");
    addToD(-2);
    ofs << "A=D" << std::endl;
    ofs << "D=M" << std::endl;
    updateValue("THIS");

    // ARG = *(FRAME - 3)  ==  ARG = SAVED_ARG
    getValue("FRAME");
    addToD(-3);
    ofs << "A=D" << std::endl;
    ofs << "D=M" << std::endl;
    updateValue("ARG");

    // LCL = *(FRAME - 4)  ==  LCL = SAVED_LCL
    getValue("FRAME");
    addToD(-4);
    ofs << "A=D" << std::endl;
    ofs << "D=M" << std::endl;
    updateValue("LCL");

    // goto RET
    at("*RET");
    jump();
}

void CodeWriter::writeFunction(std::string function_name, int num_locals)
{
    curr_func_name = function_name;
    writeComment("writeFunction " + function_name + " " + std::to_string(num_locals));
    writeLabel(function_name);
    // push 0 for num_locals times
    for (int i=0; i<num_locals; i++) writePush("constant", 0);
}

void CodeWriter::handleMemorySegmentMapping(std::string segment, int index)
{
    if (segment == "pointer" || segment == "temp") at(pointerTempMap(segment, index));
    else if (segment == "local" || segment == "argument" || segment == "this" || segment == "that") 
    {
        at("*" + register_name_map[segment]);
        for (int i=0; i<index; i++) ofs << "A=A+1" << std::endl;
    }
    else if (segment == "constant") at(index);
    else if (segment == "static") at(file_name_base + "." + std::to_string(index));
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
    writeComment(comment);
    back();
    getValue("*SP");
    ofs << opr << std::endl;
    forward();
}

void CodeWriter::writeCommandArg1Arg2(std::string opr, std::string comment="")
{
    writeComment(comment);
    back();
    getValue("*SP");
    back();
    at("*SP");
    ofs << opr << std::endl;
    forward();
}

void CodeWriter::writeCommand(std::string opr, std::string comment="")
{
    std::string curr_symbol_name = "SKIP.TO." + std::to_string(curr_symbol_idx);
    writeComment(comment);
    back();
    at("*SP");
    back();
    at("*SP");
    ofs << "D=M-D" << std::endl;
    ofs << "M=-1" << std::endl;
    at(curr_symbol_name);
    ofs << "D;" << opr << std::endl;
    at("*SP");
    ofs << "M=0" << std::endl;
    ofs << "(" << curr_symbol_name << ")" << std::endl;
    forward();
}

void CodeWriter::writeComment(std::string comment)
{
    ofs << "// " << comment << " " << std::endl;
}

void CodeWriter::at(std::string address)
{
    if (address.substr(0, 1) == "*") 
    {
        ofs << "@" << address.substr(1, address.size()-1) << std::endl;
        ofs << "A=M" << std::endl;
    }
    else
    {
        ofs << "@" << address << std::endl;
    }
}

void CodeWriter::at(int address)
{
    ofs << "@" << address << std::endl;
}

void CodeWriter::jump()
{
    ofs << "0;JEQ" << std::endl;
}

void CodeWriter::updateValue(std::string address)
{
    at(address);
    ofs << "M=D" << std::endl; 
}

void CodeWriter::getValue(std::string address)
{
    at(address);
    ofs << "D=M" << std::endl; 
}

void CodeWriter::addToD(int val)
{
    if (val>0)
    {
        at(val);
        ofs << "D=D+A" << std::endl;
    }
    else if (val<0)
    {
        at(-val);
        ofs << "D=D-A" << std::endl;
    }
}

template<typename T>
void CodeWriter::getAddress(T address)
{
    ofs << "@" << address << std::endl;
    ofs << "D=A" << std::endl; 
}

void CodeWriter::forward()
{
    at("SP");
    ofs << "M=M+1" << std::endl;
}

void CodeWriter::back() 
{
    at("SP");
    ofs << "M=M-1" << std::endl;
}

void CodeWriter::close()
{
    ofs << "(END)" << std::endl;
    at("END");
    jump();
    (ofs).close();
}