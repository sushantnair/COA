DATA SEGMENT
NUM1 DW 1234H
NUM2 DW 1234H
RES DW ?
DATA ENDS
CODE SEGMENT
ASSUME CS:CODE,DS:DATA
START:MOV AX,DATA
MOV DS,AX
MOV AX,NUM1
MOV BX,NUM2
DIV BX
MOV RES,AX
MOV AH,4CH
INT 21H
CODE ENDS
END START
