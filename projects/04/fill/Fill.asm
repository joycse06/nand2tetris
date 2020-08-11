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
@i
M=0
@0
@n
M=A
@color
M=-1
@key
M=0

(MAIN_LOOP)
  @CHANGE_SCREEN
  0;JMP
  
  @MAIN_LOOP
  0;JMP

(CHANGE_SCREEN)
  @8191
  D=A
  @n
  M=D
  @i
  M=0

  // addr = SCREEN
  @SCREEN
  D=A
  @addr
  M=D
  
  // determine pixel color
  @KBD
  D=M
  @BLACK
  D;JGT
  @WHITE
  0;JMP
  
  (BLACK)
    @color
    M=-1
    @CHANGE_PIXEL_LOOP
    0;JMP
  
  (WHITE)
    @color
    M=0
    @CHANGE_PIXEL_LOOP
    0;JMP
  
  (CHANGE_PIXEL_LOOP)
    @i
    D=M
    @n
    D=D-M
    @MAIN_LOOP
    D;JGT
  
    @color
    D=M
    @addr
    A=M
    M=D
  
    @i
    M=M+1
    @addr
    M=M+1
    @CHANGE_PIXEL_LOOP
    0;JMP
