// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
 
// Adds 1+...+100.


@R2    // sum refers to some mem. location. 
M=0     // sum=0

@R1
D=M
@i
M=-D   // i = 0 - RAM[0]

@0
D=A


(LOOP) 
@i
D=M
@END
D;JGE // If (i-R0)>0 goto END

@R0
D=M    // D is value in RAM[0]

@R2
M=D+M   //RAM[2]=RAM[2]+R0

@i
M=M+1  // i=i+1



 



@LOOP
0;JMP  // Goto LOOP
  

(END)
     @END
     0;JMP  // Infinite loop