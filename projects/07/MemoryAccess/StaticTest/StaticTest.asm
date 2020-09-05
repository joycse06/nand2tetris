// push constant 111
@111
D=A
@0
A=M
M=D
@0
M=M+1
// push constant 333
@333
D=A
@0
A=M
M=D
@0
M=M+1
// push constant 888
@888
D=A
@0
A=M
M=D
@0
M=M+1
// pop static 8
@0
M=M-1
@0
A=M
D=M
@StaticTest.8
M=D
// pop static 3
@0
M=M-1
@0
A=M
D=M
@StaticTest.3
M=D
// pop static 1
@0
M=M-1
@0
A=M
D=M
@StaticTest.1
M=D
// push static 3
@StaticTest.3
D=M
@0
A=M
M=D
@0
M=M+1
// push static 1
@StaticTest.1
D=M
@0
A=M
M=D
@0
M=M+1
// sub
@0
M=M-1
@0
A=M
D=M
@0
M=M-1
@0
A=M
D=M-D
M=D
@0
M=M+1
// push static 8
@StaticTest.8
D=M
@0
A=M
M=D
@0
M=M+1
// add
@0
M=M-1
@0
A=M
D=M
@0
M=M-1
@0
A=M
D=D+M
M=D
@0
M=M+1
