// ACADEMIC INTEGRITY PLEDGE
//
// - I have not used source code obtained from another student nor
//   any other unauthorized source, either modified or unmodified.
//
// - All source code and documentation used in my program is either
//   my original work or was derived by me from the source code
//   published in the textbook for this course or presented in
//   class.
//
// - I have not discussed coding details about this project with
//   anyone other than my instructor. I understand that I may discuss
//   the concepts of this program with other students and that another
//   student may help me debug my program so long as neither of us
//   writes anything during the discussion or modifies any computer
//   file during the discussion.
//
// - I have violated neither the spirit nor letter of these restrictions.
//
//
//
// Signed: Rhea Huber Date: 10/5/22

// 3460:426 Lab 1 - Basic C shell rev. 9/10/2020

/* Basic shell */

/*
 * This is a very minimal shell. It finds an executable in the
 * PATH, then loads it and executes it (using execv). Since
 * it uses "." (dot) as a separator, it cannot handle file
 * names like "minishell.h"
 *
 * The focus on this exercise is to use fork, PATH variables,
 * and execv.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_ARGS 64
#define MAX_ARG_LEN 16
#define MAX_LINE_LEN 80
#define WHITESPACE " ,\t\n"

struct command_t
{
    char *name;
    int argc;
    char *argv[MAX_ARGS];
};

/* Function prototypes */
int parseCommand(char *, struct command_t *);
void printPrompt();
void readCommand(char *);

int main(int argc, char *argv[])
{
    int pid;
    int status;
    char cmdLine[MAX_LINE_LEN];
    struct command_t command;

    /* Provide initial instructions */
    printf("Enter a command or enter 'H' for help\n");

    while (1)
    {
        printPrompt();
        /* Read the command line and parse it */
        readCommand(cmdLine);
        parseCommand(cmdLine, &command);
        command.argv[command.argc] = NULL;

        /*
           TODO: if the command is one of the shortcuts you're testing for
           either execute it directly or build a new command structure to
           execute next
        */
        if (*command.name == 'Q')
        {
            /* Quit the shell */
            break;
        }
        else if (*command.name == '\0')
        {
            /* Bypass fork and print a new prompt */
            continue;
        }
        else if (*command.name == 'C')
        {
            /* Execute 'copy' command */
            /* Replace shorthand with actual command */
            command.name = "cp";
            command.argv[0] = command.name;
        }
        else if (*command.name == 'D')
        {
            /* Execute 'delete' command */
            /* Replace shorthand with actual command */
            command.name = "rm";
            command.argv[0] = command.name;
        }
        else if (*command.name == 'E')
        {
            /* Execute 'echo' command */
            /* No arguments, issue new prompt */
            if (command.argc == 1)
            {
                continue;
            }

            /* Print full list of arguments, then newline */
            for (int i = 1; i < command.argc; ++i)
            {
                printf("%s", command.argv[i]);
                printf(" ");
            }
            printf("\n");
            continue;
        }
        else if (*command.name == 'H')
        {
            /* Execute 'help' command */
            /* Replace shorthand with actual command */
            printf("\nThis is a basic shell program which can be used to execute commands.\n");
            printf("Standard linux commands can be executed, as well as the following:\n");
            printf("(Note: Commands do not accept filenames including a '.')\n");
            printf("(Note: All commands listed below are case-sensitive)\n\n");
            printf("Quit    - Q                 - Exits myshell\n");
            printf("Help    - H                 - Displays this guide\n");
            printf("Copy    - C [file1] [file2] - Creates file2 as a copy of file1\n");
            printf("Delete  - D [file]          - Deletes the named file\n");
            printf("Echo    - E [comment]       - Displays the comment to the screen. Does not display '.' or ',' or multiple spaces\n");
            printf("List    - L                 - Lists the contents of the current directory\n");
            printf("Make    - M [file]          - Creates a new file with the provided name and opens it in a text editor\n");
            printf("Print   - P [file]          - Displays the contents of the named file on the screen\n");
            printf("Wipe    - W                 - Clears the screen\n");
            printf("Execute - X [program]       - Executes the named program\n\n");
            continue;
        }
        else if (*command.name == 'L')
        {
            /* Execute 'list' command */
            /* Skip a line and print current directory */
            printf("\n");
            command.name = "pwd";
            command.argv[0] = command.name;
            command.argv[1] = NULL;
            /* Create a child process to execute the command */
            if ((pid = fork()) == 0)
            {
                /* Child executing command */
                execvp(command.name, command.argv);
                /* Error message only prints if execvp() fails */
                printf("Directory could not be retrieved\n");
                exit(0);
            }
            /* Wait for child process to terminate */
            wait(&status);

            /* Skip another line and set command to 'ls -l' */
            printf("\n");
            command.name = "ls";
            command.argv[0] = command.name;
            command.argv[1] = "-l";
            command.argv[2] = NULL;
        }
        else if (*command.name == 'M')
        {
            /* Execute 'make' command */
            /* Replace shorthand with actual command */
            command.name = "nano";
            command.argv[0] = command.name;
        }
        else if (*command.name == 'P')
        {
            /* Execute 'print' command */
            /* Replace shorthand with actual command */
            command.name = "more";
            command.argv[0] = command.name;
        }
        else if (*command.name == 'W')
        {
            /* Execute 'wipe' command */
            /* Replace shorthand with actual command */
            command.name = "clear";
            command.argv[0] = command.name;
        }
        else if (*command.name == 'X')
        {
            /* Execute 'execute' command */
            /* Replace shorthand with actual command */
            command.name = command.argv[1];
            command.argv[0] = command.name;
            command.argv[1] = NULL;
        }

        /* Create a child process to execute the command */
        if ((pid = fork()) == 0)
        {
            /* Child executing command */
            execvp(command.name, command.argv);
            /* Error message only prints if execvp() fails */
            printf("Command not found\n");
            exit(0);
        }
        /* Wait for the child to terminate */
        wait(&status);
    }

    /* Shell termination */
    printf("\n\nshell: Terminating successfully\n");
    return 0;
}

/* End basic shell */

/* Parse Command function */

/* Determine command name and construct the parameter list.
 * This function will build argv[] and set the argc value.
 * argc is the number of "tokens" or words on the command line
 * argv[] is an array of strings (pointers to char *). The last
 * element in argv[] must be NULL. As we scan the command line
 * from the left, the first token goes in argv[0], the second in
 * argv[1], and so on. Each time we add a token to argv[],
 * we increment argc.
 */
int parseCommand(char *cLine, struct command_t *cmd)
{
    int argc;
    char **clPtr;
    /* Initialization */
    clPtr = &cLine; /* cLine is the command line */
    argc = 0;
    cmd->argv[argc] = (char *)malloc(MAX_ARG_LEN);
    /* Fill argv[] */
    while ((cmd->argv[argc] = strsep(clPtr, WHITESPACE)) != NULL)
    {
        cmd->argv[++argc] = (char *)malloc(MAX_ARG_LEN);
    }

    /* Set the command name and argc */
    cmd->argc = argc - 1;
    cmd->name = (char *)malloc(sizeof(cmd->argv[0]));
    strcpy(cmd->name, cmd->argv[0]);
    return 1;
}

/* End parseCommand function */

/* Print prompt and read command functions - Nutt pp. 79-80 */

void printPrompt()
{
    /* Build the prompt string to have the machine name,
     * current directory, or other desired information
     */
    char promptString[] = "linux emh135|>";
    printf("%s ", promptString);
}

void readCommand(char *buffer)
{
    /* This code uses any set of I/O functions, such as those in
     * the stdio library to read the entire command line into
     * the buffer. This implementation is greatly simplified,
     * but it does the job.
     */
    fgets(buffer, 80, stdin);
}

/* End printPrompt and readCommand */
