all: my_ls

my_ls: my_ls.o dir_ops.o
	gcc -o my_ls my_ls.o dir_ops.o -Wall -Werror -Wextra
	
dir_ops.o: dir_ops.c
	gcc -c dir_ops.c 

my_ls.o: my_ls.c
	gcc -c my_ls.c 

clean: 
	rm -f my_ls.o
	rm -f dir_ops.o

fclean: clean
	rm -f my_ls

re: all clean