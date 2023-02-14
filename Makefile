# A makefile for myshell.c

myshell: myshell.c
	ulimit -u 5
	gcc -o myshell myshell.c
