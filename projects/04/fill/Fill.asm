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




@24576
D=M



(LOOP) 
@24576
D=M  // check if keyboard input

@CLEAR
D;JEQ // If D = 0 goto CLEAR


//M=0  ? // write 0 if n	o keyboard input


(DRAW)
@512
D=A
@NUM
M=D  // number of iteration

@R0
D=A
@i
M=D  // set i = 0

(LOOP1)
@16384
D=A
@i
D=D+M // [16384+i]

A=D
M=-1  // fill 1

@i
M=M+1  // i = i+1
D=M
@8192
D=D-A  // D = i-5

@LOOP1
D;JLT  // continue loop if i < 5

// end of draw
@LOOP
0;JMP  // Goto LOOP

(CLEAR)
@512
D=A
@NUM
M=D  // number of iteration

@R0
D=A
@i
M=D  // set i = 0

(LOOP2)
@16384
D=A
@i
D=D+M // [16384+i]

A=D
M=0  // fill 1

@i
M=M+1  // i = i+1
D=M
@8192
D=D-A  // D = i-5

@LOOP2
D;JLT  // continue loop if i < 5
// end of clear

@LOOP
0;JMP  // Goto LOOP





