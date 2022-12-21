A basic shell implementation made in C.

# Installation
Requirements:  
- Linux distribution with GCC installed
- `gnome-terminal` package

The shell can be compiled using CMake:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

To run the shell:
```
$ cd build
$ ./cshell
```

# Features
- Execute external programs
- Supports program arguments
- Inbuilt commands(eg: cd, exit, help)
- Opens a new gnome terminal window when run
- The shell can display colored text

The man command can be used for information regarding other programs.

# Planned Features
- Command history: Browse and execute previous commands using the up and down arrow keys.
- Tab completion: Tab completion for commands and arguments.
- Redirection: Allow redirecting the input and output of commands using the < and > operators.
- Pipes: Allow piping the output of one command into the input of another using the | operator.

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
