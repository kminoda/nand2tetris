// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(BASE_LOOP) 
    @16384
    D = A
    @CURRENT_PIXEL
    M = 0           // Current pixel
    @KBD
    D = M
    @FILL_SCREEN
    D;JGT           // if D>0, go to FILL_SCREEN
    @EMPTY_SCREEN
    D;JEQ           // if D=0, go to EMPTY_SCREEN
(FILL_SCREEN)
    @CURRENT_PIXEL
    D = M
    @SCREEN
    A = A + D
    M = -1
    @CURRENT_PIXEL
    D = M + 1
    M = D
    @8192
    D = A - D
    @FILL_SCREEN
    D;JGT           // if D>0, go back to FILL_SCREEN (continue filling next pixel)
    @BASE_LOOP
    0;JMP           // go back to BASE_LOOP
(EMPTY_SCREEN)
    @CURRENT_PIXEL
    D = M
    @SCREEN
    A = A + D
    M = 0
    @CURRENT_PIXEL
    D = M + 1
    M = D
    @8192
    D = A - D
    @EMPTY_SCREEN
    D;JGT           // if D>0, go back to FILL_SCREEN (continue filling next pixel)
    @BASE_LOOP
    0;JMP           // go back to BASE_LOOP