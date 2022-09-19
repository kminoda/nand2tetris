#ifndef CODE_WRITER_H_
#define CODE_WRITER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

class CodeWriter
{
    private:
        std::ofstream ofs;
        CodeWriter(const CodeWriter&);
        CodeWriter& operator=(const CodeWriter&);
        std::string outfile_name;
        std::string file_name_base;
        int stack_pointer;
        int curr_symbol_idx;
    public:
        CodeWriter(std::string outfile);
        std::string getFileName(std::string infile_name);
        void writeCommand(std::string opr, std::string comment);
        void writeCommandArg(std::string opr, std::string comment);
        void writeCommandArg1Arg2(std::string opr, std::string comment);
        void setFileName(std::string filename);
        void writeArithmetic(std::string command);
        void writePush(std::string segment, int index);
        void writePop(std::string segment, int index);
        std::string pointerTempMap(std::string segment, int index);
        void handleMemorySegmentMapping(std::string segment, int index);
        void back();
        void forward();
        void go2SP();
        void fetchSPvalue();
        void close();
};

#endif // CODE_WRITER_H_