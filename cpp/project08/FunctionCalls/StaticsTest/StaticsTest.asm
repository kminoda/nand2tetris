// initialization 
@256
D=A
@SP
A=M
M=D
@Sys.init
0;JEQ
// writeFunction Class1.set 0 
// writeLabel Class1.set 
(Class1.set)
// push argument 0 
@ARG
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
// pop static 0 
@SP
M=M-1
@SP
A=M
D=M
@Class1.0
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
// pop static 1 
@SP
M=M-1
@SP
A=M
D=M
@Class1.1
M=D
// push constant 0 
@0
D=A
@SP
A=M
M=D
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
0;JEQ
// writeFunction Class1.get 0 
// writeLabel Class1.get 
(Class1.get)
// push static 0 
@Class1.0
D=M
@SP
A=M
M=D
@SP
M=M+1
// push static 1 
@Class1.1
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
0;JEQ
// writeFunction Sys.init 0 
// writeLabel Sys.init 
(Sys.init)
// push constant 6 
@6
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 8 
@8
D=A
@SP
A=M
M=D
@SP
M=M+1
// writeCall Class1.set 2 
@Class1.set.return-address.32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@7
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
// writeGoto Class1.set 
@Class1.set
0;JEQ
// writeLabel Class1.set.return-address.32766 
(Class1.set.return-address.32766)
// pop temp 0 
@SP
M=M-1
@SP
A=M
D=M
@R5
M=D
// push constant 23 
@23
D=A
@SP
A=M
M=D
@SP
M=M+1
// push constant 15 
@15
D=A
@SP
A=M
M=D
@SP
M=M+1
// writeCall Class2.set 2 
@Class2.set.return-address.32767
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@7
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
// writeGoto Class2.set 
@Class2.set
0;JEQ
// writeLabel Class2.set.return-address.32767 
(Class2.set.return-address.32767)
// pop temp 0 
@SP
M=M-1
@SP
A=M
D=M
@R5
M=D
// writeCall Class1.get 0 
@Class1.get.return-address.32768
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
// writeGoto Class1.get 
@Class1.get
0;JEQ
// writeLabel Class1.get.return-address.32768 
(Class1.get.return-address.32768)
// writeCall Class2.get 0 
@Class2.get.return-address.32769
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
// writeGoto Class2.get 
@Class2.get
0;JEQ
// writeLabel Class2.get.return-address.32769 
(Class2.get.return-address.32769)
// writeLabel WHILE 
(WHILE)
// writeGoto WHILE 
@WHILE
0;JEQ
// writeFunction Class2.set 0 
// writeLabel Class2.set 
(Class2.set)
// push argument 0 
@ARG
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
// pop static 0 
@SP
M=M-1
@SP
A=M
D=M
@Class2.0
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
// pop static 1 
@SP
M=M-1
@SP
A=M
D=M
@Class2.1
M=D
// push constant 0 
@0
D=A
@SP
A=M
M=D
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
0;JEQ
// writeFunction Class2.get 0 
// writeLabel Class2.get 
(Class2.get)
// push static 0 
@Class2.0
D=M
@SP
A=M
M=D
@SP
M=M+1
// push static 1 
@Class2.1
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
0;JEQ
(END)
@END
0;JEQ