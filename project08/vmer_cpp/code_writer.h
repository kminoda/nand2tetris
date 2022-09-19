#ifndef CODE_WRITER_H_
#define CODE_WRITER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <filesystem>

class CodeWriter
{
    private:
        std::ofstream ofs;
        std::string outfile_name;
        std::string file_name_base;
        std::string curr_func_name;
        int stack_pointer;
        int curr_call_idx;
        int curr_symbol_idx;
        bool is_directory;
    public:
        CodeWriter(const CodeWriter&);
        CodeWriter& operator=(const CodeWriter&);
        CodeWriter(std::string outfile);

        std::string getFileName(std::string infile_name);
        void setFileName(std::string filename);

        void writeInit();
        void writePush(std::string segment, int index);
        void writePop(std::string segment, int index);
        void writeArithmetic(std::string command);
        void writeLabel(std::string label, bool add_func_name=false);
        void writeGoto(std::string label, bool add_func_name=false);
        void writeIf(std::string label, bool add_func_name=false);
        void writeCall(std::string function_name, int num_args);
        void writeReturn();
        void writeFunction(std::string function_name, int num_locals);

        void writeCommand(std::string opr, std::string comment);
        void writeCommandArg(std::string opr, std::string comment);
        void writeCommandArg1Arg2(std::string opr, std::string comment);
        void writeComment(std::string comment);

        std::string pointerTempMap(std::string segment, int index);
        void handleMemorySegmentMapping(std::string segment, int index);
        void back();
        void forward();
        void at(std::string address);
        void at(int address);
        void jump();
        void getValue(std::string address);
        void updateValue(std::string address);
        void addToD(int val);
        void close();

        template<typename T>
        void getAddress(T address);
};

#endif // CODE_WRITER_H_