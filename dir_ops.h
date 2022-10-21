#ifndef STRUCT_DIRENT_ENTRY
#define STRUCT_DIRENT_ENTRY
typedef struct s_dirent_entry {
  char *dir_name;
  time_t t_sec;
  long int t_nsec;
} dirent_entry;
#endif

#ifndef STRUCT_DIRENT_ARRAY
#define STRUCT_DIRENT_ARRAY
typedef struct s_dirent_array {
  int size;
  struct s_dirent_entry **array;
} dirent_array;
#endif

//Count the number of entries in dir_name directory
int count_entries(char *dir_name, int aflag);

//Check if directory is found
int check_dir(char *directory);