#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define cshell_RL_BUFSIZE 1024
#define cshell_TOK_BUFSIZE 64
#define cshell_TOK_DELIM " \t\r\n\a"
#define BUILTIN_COMMAND_COUNT 3

int cshell_cd(char **args);
int cshell_help(char **args);
int cshell_exit(char **args);
char *cshell_read_line(void);
char **cshell_split_line(char *line);
void cshell_loop(void);
int cshell_execute(char **args);

int main(int argc, char **argv)
{
    // Run command loop.
    cshell_loop();
    return EXIT_SUCCESS;
}

char *builtin_commands[] = {
    "cd",
    "help",
    "exit"};

int (*builtin_funcs[])(char **) = {
    &cshell_cd,
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
            perror("CShell");
        }
    }
    return 1;
}

void cshell_loop(void)
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("> ");
        line = cshell_read_line();
        args = cshell_split_line(line);
        status = cshell_execute(args);

        free(line);
        free(args);
    } while (status == 1);
}

// Reads a line of text from stdin
char *cshell_read_line(void)
{
    int position = 0;
    int bufsize = cshell_RL_BUFSIZE;
    char *buffer = malloc(sizeof(char) * bufsize);

    // This is an integer and not a char as EOF is an integer
    int c;
    if (!buffer)
    {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // Keep adding to the string until newline or EOF is encountered.
    while (1)
    {
        c = getchar();
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        // If string size is greater than current buffer size, we realloc buffer
        if (position >= bufsize)
        {
            bufsize += cshell_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer)
            {
                fprintf(stderr, "Memory allocation error.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

// read_line function but using the getline() function that does most of the work for us
char *cshell_read_line_simple(void)
{
    char *line = NULL;
    ssize_t bufsize = 0; // Make getline realloc buffer
    if (getline(&line, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        { // Check for EOF
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("Readline error!\n");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

// Function to parse input line into list of arguments.
// This function does not account for escaping using quotes
// Arguments are separated by whitespace
char **cshell_split_line(char *line)
{
    int bufsize = cshell_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    // strtok tokenizes given string wrt the specified delimiters
    token = strtok(line, cshell_TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        // Reallocate memory if bufsize too small
        if (position >= bufsize)
        {
            bufsize += cshell_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "Memory allocation error!\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, cshell_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

// The process running this program creates a clone of itself
// using fork() and the child process runs exec() and replaces
// itself with the process we want to launch. wait() can be used
// by the parent process to do other things
int cshell_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("Error!\n");
        }
        exit(EXIT_FAILURE);
    }
    // fork()
    else if (pid < 0)
    {
        perror("Error forking!\n");
    }
    // fork() executed successfully
    else
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int cshell_execute(char **args)
{
    if (args[0] == NULL)
    {
        return 1;
    }

    for (int i = 0; i < BUILTIN_COMMAND_COUNT; i++)
    {
        if (strcmp(args[0], builtin_commands[i]) == 0)
        {
            return (*builtin_funcs[i])(args);
        }
    }
    return cshell_launch(args);
}