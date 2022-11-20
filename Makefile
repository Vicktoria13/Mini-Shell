EXEC = main
CFLAGS =   -ggdb3


# taper dans le terminal ./main
#taper make vclean pour supprimer les fichiers .o

all: $(EXEC)


main: main.c fonction_split_stdin.h fonction_split_stdin.c  launch_shell.h launch_shell.c builtin_function.h builtin_function.c
	gcc $(CFLAGS) -o main main.c fonction_split_stdin.c launch_shell.c builtin_function.c

clean:
	rm -f *.o *~ *.backup

vclean:	clean
	rm -f $(EXEC) text.txt
