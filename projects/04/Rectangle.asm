// Program: Rectangle.asm
// Draw a Rectangle on the screen

@R0
D=M
@n
M=D // n = RAM[0]


@i
M=0 // i = 0

@SCREEN
D=A
@addr
M=D // address = 16384 (base address of Hack screen)

(LOOP)
  @i
  D=M
  @n
  D=D-M
  @END
  D;JGT

  @addr
  A=M
  M=-1 // RAM[addr]=1111111111111111

  @i
  M=M+1 // i = i + 1
  @32
  D=A
  @addr
  M=D+M // addr = addr + 32
  @LOOP
  0;JMP // goto LOOP


(END)
  @END
  0;JMP

