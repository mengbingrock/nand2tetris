//push constant 111
@111
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 333
@333
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 888
@888
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//pop constant 
@8
D=A
@StaticTest.8
//add base
//pointer or static type: do not add to base 
D=A
//swap A D using stack
@SP
A=M
M=D
@SP
A=M-1
D=M
@SP
A=M
A=M
M=D
//move backward the stack
@SP
M=M-1
//pop constant 
@3
D=A
@StaticTest.3
//add base
//pointer or static type: do not add to base 
D=A
//swap A D using stack
@SP
A=M
M=D
@SP
A=M-1
D=M
@SP
A=M
A=M
M=D
//move backward the stack
@SP
M=M-1
//pop constant 
@1
D=A
@StaticTest.1
//add base
//pointer or static type: do not add to base 
D=A
//swap A D using stack
@SP
A=M
M=D
@SP
A=M-1
D=M
@SP
A=M
A=M
M=D
//move backward the stack
@SP
M=M-1
//push constant 3
@3
D=A
@StaticTest.3
//add base
//pointer or static type: do not add to base 
D=M
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 1
@1
D=A
@StaticTest.1
//add base
//pointer or static type: do not add to base 
D=M
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
//sub
M=M-D
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 8
@8
D=A
@StaticTest.8
//add base
//pointer or static type: do not add to base 
D=M
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
