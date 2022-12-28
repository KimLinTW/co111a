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
// 本程式是模仿老師的程式

(CHECK) // 檢查 變數i 是否在16384~24576範圍間 有的話變色
  @16384
  D=A
  @i
  M=D
(LOOP)
  @24576
  D=A
  @i
  D=M-D
  @FINISH
  D;JGE

  @color
  M=0
  @24576
  D=M
  @BREAK
  D;JEQ
  
  @color
  M=-1
(BREAK)
  @color
  D=M
  @i
  A=M
  M=D
  @i
  M=M+1
  @LOOP
  0;JMP
(FINISH)
  @CHECK
  0;JMP