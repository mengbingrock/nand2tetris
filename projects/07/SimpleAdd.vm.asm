//push constant 7
@7
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 8
@8
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
@SP
A=M-1
D=M
A=A-1
//add
M=M+D
@SP
M=M-1
//end of C_ARITHMETIC
