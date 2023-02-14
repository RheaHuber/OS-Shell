Directions for using myshell
A simple shell program based on the seed code provided for this course

COMPILE AND RUN (with make and g++):
1. In the directory containing "myshell.c" and "Makefile", use the command 'make'
2. In the directory containing "myshell", use the command './myshell'

COMPILE AND RUN (with g++, without make):
1. In the directory containing "myshell.c", use the commands 'ulimit -u 5' and 'gcc -o myshell myshell.c'
2. In the directory containing "myshell", use the command './myshell'

HOW TO USE:
Enter a command and its parameters and it will be executed by the shell.
The shell does not accept inputs including periods ('.').
The shell can execute standard linux commands, as well as a set of (case-sensitive) commands listed in the section below.

INCLUDED COMMANDS:

NAME    - COMMAND           - DESCRIPTION

Quit    - Q                 - Exits myshell
Help    - H                 - Displays this guide
Copy    - C [file1] [file2] - Creates file2 as a copy of file1
Delete  - D [file]          - Deletes the named file
Echo    - E [comment]       - Displays the comment to the screen. Does not display '.' or ',' or multiple spaces
List    - L                 - Lists the contents of the current directory
Make    - M [file]          - Creates a new file with the provided name and opens it in a text editor
Print   - P [file]          - Displays the contents of the named file on the screen
Wipe    - W                 - Clears the screen
Execute - X [program]       - Executes the named program
