A basic shell implementation made in C.

# Installation
Compatible on Linux distros which have GCC installed.  

The shell can be compiled using `gcc -Wall main.c builtins.c -o main`  

The command `./main` can be used to run it after compilation.

# Functionality
The shell can execute external programs and supports program arguments. 

Inbuilt Commands:
- cd
- exit
- help  

The man command can be used for information regarding other programs.
    

# Lifetime of the Shell
The shell in its lifetime has 3 basic states:
1. Initialization: Configuration files are read and executed and the shells behavior is based on this.
2. Execution: Commands are read from input and executed and the output is displayed in the shell.
3. Termination: Any pending commands are executed, shell shutdown process is initiated and memory is freed.

# Execution State Loop
The execution state of the shell is a loop where three basic things are done:
- A command is __read__ from the standard input.
- The command string is __parsed__ and arguments are extracted.
- The parsed command is __executed__ and output is displayed.

# References
- https://www.geeksforgeeks.org/making-linux-shell-c/
- https://brennan.io/2015/01/16/write-a-shell-in-c/
