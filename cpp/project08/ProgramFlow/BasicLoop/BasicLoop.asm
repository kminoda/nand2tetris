// initialization 
@256
D=A
@SP
A=M
M=D
// push constant 0 
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
// pop local 0 
@SP
M=M-1
@SP
A=M
D=M
@LCL
A=M
M=D
// writeLabel LOOP_START 
(LOOP_START)
// push argument 0 
@ARG
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
// push local 0 
@LCL
A=M
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
// pop local 0 
@SP
M=M-1
@SP
A=M
D=M
@LCL
A=M
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
// push argument 0 
@ARG
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
// writeIf LOOP_START 
@SP
M=M-1
@SP
A=M
D=M
@LOOP_START
D;JNE
// push local 0 
@LCL
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
(END)
@END
0;JMP
