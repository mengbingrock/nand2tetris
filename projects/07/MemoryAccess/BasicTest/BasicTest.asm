//push constant 10
@10
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
@LCL
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
//push constant 21
@21
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 22
@22
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
@ARG
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
//pop constant 
@1
D=A
@ARG
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
//push constant 36
@36
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
//push constant 42
@42
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 45
@45
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//pop constant 
@5
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
//pop constant 
@2
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
//push constant 510
@510
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
@5
//add base
A=A+D
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
@LCL
//add base
A=M+D
D=M
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 5
@5
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
//push constant 1
@1
D=A
@ARG
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
//push constant 6
@6
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
//add
M=M+D
@SP
M=M-1
//end of C_ARITHMETIC
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
@5
//add base
A=A+D
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
