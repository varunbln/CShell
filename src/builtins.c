#include <stdio.h>
#include "builtins.h"
#include <string.h>
#include <unistd.h>

int cshell_cd(char **args);
int cshell_help(char **args);
int cshell_exit(char **args);

char *builtin_commands[] =
    {"cd",
     "help",
     "exit"};

/*
Array of function pointers, where each element of the array is a pointer to an
inbuilt function that takes a char**, a pointer to an array of strings, which
serve as the function arguments and returns an int.*/
int (*builtin_funcs[])(char **) =
    {&cshell_cd,
     &cshell_help,
     &cshell_exit};

int cshell_exit(char **args)
{
    return 0;
}

int cshell_help(char **args)
{
    printf("Type program names with any arguments, and press enter.\n");
    printf("Builtin Commands: \n");
    for (int i = 0; i < BUILTIN_COMMAND_COUNT; i++)
    {
        printf("%s\n", builtin_commands[i]);
    }
    printf("The man command can be used for information regarding other programs.\n");
    return 1;
}

int cshell_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "Expected argument to 'cd'\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("Error");
        }
    }
    return 1;
}

int run_builtins(char **args)
{
    for (int i = 0; i < BUILTIN_COMMAND_COUNT; i++)
    {
        if (strcmp(args[0], builtin_commands[i]) == 0)
        {
            // Calls the builtin function using the array of function pointers defined.
            return (*builtin_funcs[i])(args);
        }
    }
    return NO_BUILTIN_FOUND;
}