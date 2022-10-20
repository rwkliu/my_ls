#ifndef STRUCT_DIRENT_ARRAY
#define STRUCT_DIRENT_ARRAY
typedef struct s_dirent_array {
  int size;
  struct dirent **array;
} dirent_array;
#endif

//Count the number of entries in dir_name directory
int count_entries(char *dir_name, int aflag);

//Check if directory is found
int check_dir(char *directory);