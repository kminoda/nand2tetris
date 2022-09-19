// initialization 
@256
D=A
@SP
A=M
M=D
// push argument 1 
@ARG
A=M
A=A+1
D=M
@SP
A=M
M=D
@SP
M=M+1
// pop pointer 1 
@SP
M=M-1
@SP
A=M
D=M
@THAT
M=D
// push constant 0 
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop that 0 
@SP
M=M-1
@SP
A=M
D=M
@THAT
A=M
M=D
// push constant 1 
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop that 1 
@SP
M=M-1
@SP
A=M
D=M
@THAT
A=M
A=A+1
M=D
// push argument 0 
@ARG
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
// push constant 2 
@2
D=A
@SP
A=M
M=D
@SP
M=M+1
// sub 
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M-D
@SP
M=M+1
// pop argument 0 
@SP
M=M-1
@SP
A=M
D=M
@ARG
A=M
M=D
// writeLabel MAIN_LOOP_START 
(MAIN_LOOP_START)
// push argument 0 
@ARG
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
// writeIf COMPUTE_ELEMENT 
@SP
M=M-1
@SP
A=M
D=M
@COMPUTE_ELEMENT
D;JNE
// writeGoto END_PROGRAM 
@END_PROGRAM
0;JEQ
// writeLabel COMPUTE_ELEMENT 
(COMPUTE_ELEMENT)
// push that 0 
@THAT
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
// push that 1 
@THAT
A=M
A=A+1
D=M
@SP
A=M
M=D
@SP
M=M+1
// add 
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=D+M
@SP
M=M+1
// pop that 2 
@SP
M=M-1
@SP
A=M
D=M
@THAT
A=M
A=A+1
A=A+1
M=D
// push pointer 1 
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
// push constant 1 
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
// add 
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=D+M
@SP
M=M+1
// pop pointer 1 
@SP
M=M-1
@SP
A=M
D=M
@THAT
M=D
// push argument 0 
@ARG
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
// push constant 1 
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
// sub 
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M-D
@SP
M=M+1
// pop argument 0 
@SP
M=M-1
@SP
A=M
D=M
@ARG
A=M
M=D
// writeGoto MAIN_LOOP_START 
@MAIN_LOOP_START
0;JEQ
// writeLabel END_PROGRAM 
(END_PROGRAM)
(END)
@END
0;JMP
