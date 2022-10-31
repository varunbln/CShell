cshell: src/main.c src/builtins.c
	gcc -o cshell src/main.c src/builtins.c