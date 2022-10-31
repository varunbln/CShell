cshell: main.c builtins.c
	gcc -o cshell main.c builtins.c