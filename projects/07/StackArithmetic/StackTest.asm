//push constant 17
@17
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 17
@17
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
//eq,lt,gt
D=M-D
M=0
@eq1
D;JNE
@SP
A=M-1
A=A-1
M=1
(eq1)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 17
@17
D=A
@SP
A=M
M=D
//move forward the stack
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
@SP
A=M-1
D=M
A=A-1
//eq,lt,gt
D=M-D
M=0
@eq2
D;JNE
@SP
A=M-1
A=A-1
M=1
(eq2)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 16
@16
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 17
@17
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
//eq,lt,gt
D=M-D
M=0
@eq3
D;JNE
@SP
A=M-1
A=A-1
M=1
(eq3)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 892
@892
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 891
@891
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
//eq,lt,gt
D=M-D
M=0
@lt4
D;JGE
@SP
A=M-1
A=A-1
M=1
(lt4)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 891
@891
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 892
@892
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
//eq,lt,gt
D=M-D
M=0
@lt5
D;JGE
@SP
A=M-1
A=A-1
M=1
(lt5)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 891
@891
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 891
@891
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
//eq,lt,gt
D=M-D
M=0
@lt6
D;JGE
@SP
A=M-1
A=A-1
M=1
(lt6)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 32767
@32767
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 32766
@32766
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
//eq,lt,gt
D=M-D
M=0
@gt7
D;JLE
@SP
A=M-1
A=A-1
M=1
(gt7)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 32766
@32766
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 32767
@32767
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
//eq,lt,gt
D=M-D
M=0
@gt8
D;JLE
@SP
A=M-1
A=A-1
M=1
(gt8)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 32766
@32766
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 32766
@32766
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
//eq,lt,gt
D=M-D
M=0
@gt9
D;JLE
@SP
A=M-1
A=A-1
M=1
(gt9)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 57
@57
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 31
@31
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 53
@53
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
//push constant 112
@112
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
//sub
M=D-M
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 82
@82
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 17
@17
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 17
@17
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
//eq,lt,gt
D=M-D
M=0
@eq1
D;JNE
@SP
A=M-1
A=A-1
M=1
(eq1)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 17
@17
D=A
@SP
A=M
M=D
//move forward the stack
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
@SP
A=M-1
D=M
A=A-1
//eq,lt,gt
D=M-D
M=0
@eq2
D;JNE
@SP
A=M-1
A=A-1
M=1
(eq2)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 16
@16
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 17
@17
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
//eq,lt,gt
D=M-D
M=0
@eq3
D;JNE
@SP
A=M-1
A=A-1
M=1
(eq3)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 892
@892
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 891
@891
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
//eq,lt,gt
D=M-D
M=0
@lt4
D;JGE
@SP
A=M-1
A=A-1
M=1
(lt4)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 891
@891
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 892
@892
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
//eq,lt,gt
D=M-D
M=0
@lt5
D;JGE
@SP
A=M-1
A=A-1
M=1
(lt5)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 891
@891
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 891
@891
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
//eq,lt,gt
D=M-D
M=0
@lt6
D;JGE
@SP
A=M-1
A=A-1
M=1
(lt6)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 32767
@32767
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 32766
@32766
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
//eq,lt,gt
D=M-D
M=0
@gt7
D;JLE
@SP
A=M-1
A=A-1
M=1
(gt7)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 32766
@32766
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 32767
@32767
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
//eq,lt,gt
D=M-D
M=0
@gt8
D;JLE
@SP
A=M-1
A=A-1
M=1
(gt8)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 32766
@32766
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 32766
@32766
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
//eq,lt,gt
D=M-D
M=0
@gt9
D;JLE
@SP
A=M-1
A=A-1
M=1
(gt9)
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 57
@57
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 31
@31
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
//push constant 53
@53
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
//push constant 112
@112
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
//sub
M=M-D
@SP
M=M-1
//end of C_ARITHMETIC
//push constant 82
@82
D=A
@SP
A=M
M=D
//move forward the stack
@SP
M=M+1
