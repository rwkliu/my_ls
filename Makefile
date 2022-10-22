	# gcc -o my_ls my_ls.o -Wall -Wextra -Werror
	# gcc -c my_ls.c -Wall -Wextra -Werror
all: my_ls

my_ls: my_ls.o dir_ops.o
	gcc -o my_ls my_ls.o dir_ops.o 
	
dir_ops.o: dir_ops.c
	gcc -c dir_ops.c -Wall -Wextra -Werror

my_ls.o: my_ls.c
	gcc -c my_ls.c -Wall -Wextra -Werror

clean: 
	rm -f my_ls.o
	rm -f dir_ops.o

fclean: clean
	rm -f my_ls

re: all clean