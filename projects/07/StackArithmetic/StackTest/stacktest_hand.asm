// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/07/StackArithmetic/StackTest/StackTest.vm

// Executes a sequence of arithmetic and logical operations
// on the stack. 
//push constant 17
//push constant 17
//eq


//push constant 17
@17
D=A
@SP
A=M
M=D
// move forward the stack
@SP
M=M+1

//push constant 17
@17
D=A
@SP
A=M
M=D

// move forward the stack
@SP
M=M+1

//eq
@SP
A=M-1
D=M
A=A-1
D=D-M

@SP
A=M-1
A=A-1
M=0

@eq1
D;JNE
M=1

(eq1)
@SP
M=M-1




//push constant 17
//push constant 16
//eq

//push constant 17
@17
D=A
@SP
A=M
M=D
// move forward the stack
@SP
M=M+1

//push constant 16
@16
D=A
@SP
A=M
M=D

//move forward the stack
@SP
M=M+1

//lt
@SP
A=M-1
D=M
A=A-1
D=D-M

@lt0
D;JLT
@SP
A=M-1
A=A-1
M=0
@SP
M=M-1
@lt1

(lt0)
@SP
A=M-1
A=A-1
M=1
@SP
M=M-1
(lt1)

//push constant 32767
//push constant 32766
//gt

//push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

//gt
@SP
A=M-1
D=M
A=A-1
D=D-M

@gt1
D;JGT
@SP
A=M-1
A=A-1
M=0
@SP
M=M-1
@gt0
0;JMP

(gt1)
@SP
A=M-1
A=A-1
M=1
@SP
M=M-1
(gt0)

//push constant 31
//push constant 53

//push constant 31
@31
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 53
@53
D=A
@SP
A=M
M=D
@SP
M=M+1


//sub
@SP
A=M-1
D=M
A=A-1
M=D-M
@SP
M=M-1

//neg
@SP
A=M-1
M=-M



//and
@SP
A=M-1
D=M
A=A-1
M=D&M
// move back the stack
@SP
M=M-1

//or
@SP
A=M-1
D=M
A=A-1
M=D|M
// move back the stack
@SP
M=M-1

//not
@SP
A=M-1
D=M
A=A-1

A=A+1
M=!M
@SP
M=M+1

// move back the stack
@SP
M=M-1


