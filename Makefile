all: my_ls

my_ls: my_ls.o
	# gcc -o my_ls my_ls.o -Wall -Wextra -Werror
	gcc -o my_ls my_ls.o

my_ls.o: my_ls.c
	# gcc -c my_ls.c -Wall -Wextra -Werror
	gcc -c my_ls.c

clean: 
	rm -f my_ls.o

fclean: clean
	rm -f my_ls

re: all clean