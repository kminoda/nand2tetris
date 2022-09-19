@16
D=A
@SP
M=D
// push start constant,7
@7
D=A
@SP
A=M
M=D
// push end constant,7
// increment start
@SP
M=M+1
// increment end
// increment end
// push start constant,8
@8
D=A
@SP
A=M
M=D
// push end constant,8
// increment start
@SP
M=M+1
// increment end
// increment end
//  decrement start
@SP
M=M-1
//  decrement end
@SP
A=M
D=M
// 一つ目
//  decrement start
@SP
M=M-1
//  decrement end
@SP
A=M
M=M+D
// 計算
// increment start
@SP
M=M+1
// increment end
(END)
@END
0;JMP
