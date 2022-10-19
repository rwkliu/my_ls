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

//Open the directory
void open_folder(char *directory) {
  DIR *folder = opendir(directory);
  if(folder == NULL) {
      printf("Unable to open directory %s\n", directory);
    }
    else {
      printf("Directory %s is opened!\n", directory);
    }
}

int main(int argc, char *argv[]) {
  DIR *folder = NULL;
  int aflag = 0;
  int tflag = 0;
  int curr_opt;
  struct dirent *entry;
  // struct stat filestat;
  
  //Parse the optional arguments
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
    open_folder(argv[i]);
  }
  //If the non-option arguments were invalid directories, open the current directory
  if(folder == NULL) {
    open_folder(".");
  }
  return 0;
}