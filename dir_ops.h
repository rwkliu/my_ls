#ifndef STRUCT_DIRENT_ENTRY
#define STRUCT_DIRENT_ENTRY
typedef struct s_dirent_entry {
  char *entry_name;
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

//Sort dirent array entries
dirent_array *sort_entries(dirent_array *dirents, int aflag, int tflag);

//Get each entry d_name, tv_sec, and tv_nsec values
dirent_array *get_entries(char *dir_name, dirent_array *dirents, int aflag, int tflag);

//Count the number of entries in dir_name directory
int count_entries(char *dir_name, int aflag);

//Check if directory is found
int check_dir(char *directory);