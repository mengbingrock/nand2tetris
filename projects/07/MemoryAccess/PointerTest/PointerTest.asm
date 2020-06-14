//push constant 3030
@3030
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//pop constant 
@0
D=A
@THIS
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
//push constant 3040
@3040
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//pop constant 
@1
D=A
@THAT
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
//push constant 32
@32
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//pop constant 
@2
D=A
@THIS
//add base
A=M+D
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
//push constant 46
@46
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//pop constant 
@6
D=A
@THAT
//add base
A=M+D
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
//push constant 0
@0
D=A
@THIS
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
@THAT
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
//push constant 2
@2
D=A
@THIS
//add base
A=M+D
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
//push constant 6
@6
D=A
@THAT
//add base
A=M+D
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
