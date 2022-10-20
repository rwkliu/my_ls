//My version of the ls command with -a and -t options
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#ifndef STRUCT_DIRENT_ARRAY
#define STRUCT_DIRENT_ARRAY
typedef struct s_dirent_array {
  int size;
  char **array;
} dirent_array;
#endif

//Check if directory is found
int check_dir(char *directory) {
  DIR *dir = opendir(directory);
  if(dir == NULL) {
      return 1;
    }
  else {
    return 0;
  }
}

int count_entries(DIR *directory) {
  int entries = 0;
  struct dirent *dir_entry;

  while(dir_entry = readdir(directory)) {
    entries++;
  }
  return entries;
}

int main(int argc, char *argv[]) {
  DIR *folder = NULL;
  int aflag = 0;
  int tflag = 0;
  int num_files = 0;
  int curr_opt;
  struct dirent *entry;
  struct stat filestat;
  
  //Parse the optional arguments that start with '-'
  while((curr_opt = getopt(argc, argv, "at")) != -1) {
    switch(curr_opt){
      case 'a':
        aflag = 1;
        break;
      case 't':
        tflag = 1;
        break;
    }
  }
  printf("aflag = %d, tflag = %d\n", aflag, tflag);
  //Parse the non-option arguments
  for(int i = optind; i < argc; i++) {
    printf("Non-option argument %d %s\n", i, argv[i]);
    if(check_dir(argv[i]) == 1) {
      printf("Unable to open directory\n");
      return 1;
    }
    else {
      folder = opendir(argv[i]);
      printf("Directory opened\n");
    }
  }
  //If no non-options arguments were valid directories, open the current directory
  if(folder == NULL) {
    folder = opendir(".");
    printf("Default: current directory opened\n");
  }

  //Read directory entries
  entry = readdir(folder);
  num_files = count_entries(folder);
  printf("Number of files: %d\n", num_files);
  
  return 0;
}