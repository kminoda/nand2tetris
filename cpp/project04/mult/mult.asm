// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

    @R2         
    M = 0       // R2 = 0
    @COUNTR1
    M = 1       // COUNTR1 = 1
(LOOP) 
    @COUNTR1
    D = M       // D = COUNTR1
    @R1
    D = D - M   // D = COUNTR1 - R1
    @END
    D;JGT       // goto END if COUNTR1 - R1 > 0
    @R0         
    D = M       // D = R0
    @R2         
    M = D + M   // R2 = R2 + D = R2 + R0
    @COUNTR1
    M = M + 1   // COUNTR1 += 1
    @LOOP 
    0;JMP       // goto LOOP 
(END)
    @END
    0;JMP



