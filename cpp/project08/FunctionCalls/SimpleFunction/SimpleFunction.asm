// initialization 
@256
D=A
@SP
A=M
M=D
// writeFunction SimpleFunction.test 2 
// writeLabel SimpleFunction.test 
(SimpleFunction.test)
// push constant 0 
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 0 
@0
D=A
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
// push local 1 
@LCL
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
// not 
@SP
M=M-1
@SP
A=M
D=M
M=!D
@SP
M=M+1
// push argument 0 
@ARG
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
// writeReturn 
@LCL
D=M
@FRAME
M=D
@5
D=D-A
A=D
D=M
@RET
M=D
@SP
M=M-1
@SP
A=M
D=M
@ARG
A=M
M=D
@ARG
D=M
@1
D=D+A
@SP
M=D
@FRAME
D=M
@1
D=D-A
A=D
D=M
@THAT
M=D
@FRAME
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@FRAME
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@FRAME
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@RET
A=M
0;JMP
(END)
@END
0;JMP
